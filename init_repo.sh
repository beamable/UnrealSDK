#!/bin/sh

if ! command -v dotnet >/dev/null 2>&1; then
    echo ".NET is not installed."
    exit 1
fi

# Verify that the dotnet tool is callable by listing installed tools
if ! dotnet tool list >/dev/null 2>&1; then
    echo "The dotnet tool cannot be called, which may indicate a misconfiguration. Make sure that Dotnet SDK is installed."
    exit 1
fi

# Ensure we are inside a unreal project root folder.
if [ ! -f *.uproject ]; then
   echo "Please run this script from inside a folder containing a .uproject (your Unreal Project's root)."
   exit 1
fi

# Copy the Sandbox plugin over to the plugin folder.
# This is a local-only plugin that you can do whatever you want in.
# It is not committed to the repo and it is the default plugin configured to load
# (this means the repo won't work unless you run this script exactly once first).

echo "$pwd"
cd $pwd

SANDBOX_PROJ_NAME="BEAMPROJ_Sandbox"
PLUGIN_SANDBOX_PATH="$(pwd)/Plugins/$SANDBOX_PROJ_NAME"
TEMPLATE_SANDBOX_PATH="$(pwd)/Templates/Plugins/$SANDBOX_PROJ_NAME"

if [ ! -d "Microservices/services/MSPlayground" ]; then
    echo "Creating BEAMPROJ_Sandbox Plugin"
    mkdir -p "$PLUGIN_SANDBOX_PATH"
    cp -r "$TEMPLATE_SANDBOX_PATH"/* "$PLUGIN_SANDBOX_PATH"
fi

# Read out the expected version of the CLI
CLI_VERSION=0.0.123

# Check if the beam CLI is installed globally and if not install it.
if ! command -v beam >/dev/null 2>&1; then
    echo "Please run the Set-Packages script from our cli project before running this script."  
fi

# Restore the Beamable.Tools tool defined in the '.config/dotnet-tools.json' file
# If you see an error here, please run the set-packages.sh script with the first argument as the path to the root of this repository.
dotnet tool restore

# Create a microservice
if [ ! -d "Microservices/services/MSPlayground" ]; then
    echo "Creating MSPlayground microservice for local development."
    beam project new service MSPlayground --sln "Microservices/Microservices.sln" --logs v
fi

# Create a microstorage
if [ ! -d "Microservices/services/DBPlayground" ]; then
    echo "Creating DBPlayground storage for local development."
    beam project new storage DBPlayground --sln "Microservices/Microservices.sln" --link-to MSPlayground --logs v
fi
