#!/bin/sh

if ! command -v dotnet >/dev/null 2>&1; then
    echo ".NET is not installed."
    return 1
fi

# Verify that the dotnet tool is callable by listing installed tools
if ! dotnet tool list >/dev/null 2>&1; then
    echo "The dotnet tool cannot be called, which may indicate a misconfiguration. Make sure that Dotnet SDK is installed."
    return 1
fi

# Install the SDK in your project
# Find the .uproject file path and name
UPROJECT_PATH=$(find . -name "*.uproject" -print -quit)
echo "Found .uproject: $UPROJECT_PATH"

# Ensure we are inside a unreal project root folder.
if [ $UPROJECT_PATH == "" ]; then
   echo "Please run this script from inside a folder containing a .uproject (your Unreal Project's root)."
   return 1
fi

# Copy the Sandbox plugin over to the plugin folder.
# This is a local-only plugin that you can do whatever you want in.
# It is not committed to the repo and it is the default plugin configured to load
# (this means the repo won't work unless you run this script exactly once first).
SANDBOX_PROJ_NAME="BEAMPROJ_Sandbox"
PLUGIN_SANDBOX_PATH="$(pwd)/Plugins/$SANDBOX_PROJ_NAME"
TEMPLATE_SANDBOX_PATH="$(pwd)/Templates/Plugins/$SANDBOX_PROJ_NAME"

if [ ! -d "$PLUGIN_SANDBOX_PATH" ]; then
    echo "Creating BEAMPROJ_Sandbox Plugin"
    mkdir -p "$PLUGIN_SANDBOX_PATH"
    cp -r "$TEMPLATE_SANDBOX_PATH"/* "$PLUGIN_SANDBOX_PATH"
fi

# Restore the Beamable.Tools tool defined in the '.config/dotnet-tools.json' file
# If you're in our dev-branch and this errors out, please run the set-packages.sh script with the first argument as the path to the root of this repository.
# If you're in our main-branch and this errors out, please make sure '.config/dotnet-tools.json' is pointed at a valid and released CLI version.  
echo "Installing the Beam CLI in this project"
dotnet tool restore

# We export some EnvVars so that the `dotnet beam project new` commands see these
# This is important so that this works from inside GitHub Actions (when running inside a container)
# It fixes this script so that the microservices CSPROJ files see these EnvVars and function properly when inside a docker container.  
DotNetConfigPath="$(pwd)"
echo "Setting DotNetConfigPath as an EnvVar: $DotNetConfigPath"
export DotNetConfigPath

BeamableVersion=$(
  # Read the UnrealSDK's own dotnet-tools manifest.
  sed -e 's/^ *//' < "$(pwd)/.config/dotnet-tools.json" |
    # Make it into a single line
    tr -d '\n' |
    # Extract everything from "beamable.tools" until the first comma after the first value between quotes. 
    # It prints out this: "beamable.tools": {"version": "0.0.123"    
    grep -Eo '"beamable.tools": {"version": "[^,]*"' |
    # Extract the semantic version number out of that string
    # It prints out this: 0.0.123"
    grep -Eo '[0-9]+.[0-9]+.[0-9]+.*' |
    # Extract all double-quotes
    # It prints out this: 0.0.123
    sed 's/"$//'
)
echo "Setting BeamableVersion as an EnvVar: $BeamableVersion"
export BeamableVersion


# Create a playground microservice/storage that is ignored in Git.
# Use this to write quick and dirty MS code.
# Feel free to create a realm in our shared org with your name and "devname-playground" and ONLY EVER DEPLOY THIS TO THIS REALM.
# Keep an eye to not commit the clients to this MS.
# Running this script will always clean up the playground services.  
if [ -d "Microservices/services/MSPlayground" ]; then
  rm -rf "Microservices/services/MSPlayground"
fi
echo "Creating MSPlayground microservice for local development."
dotnet beam project new service MSPlayground --sln "Microservices/Microservices.sln" --logs v --groups BEAMPROJ_Sandbox

if [ -d "Microservices/services/DBPlayground" ]; then
  rm -rf "Microservices/services/DBPlayground"
fi
echo "Creating DBPlayground storage for local development."
dotnet beam project new storage DBPlayground --sln "Microservices/Microservices.sln" --quiet --logs v --groups BEAMPROJ_Sandbox
dotnet beam project deps add MSPlayground DBPlayground


if [ $# -eq 0 ] # No arguments supplied
  then
    echo "Script finished executing, press any key to exit"
    read
fi