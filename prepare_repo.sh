#!/bin/sh


# ARGS LIST
CLEAN_SANDOBOX_ARG="--clean-sandbox"
SKIP_WAITING_ARG="--skip-waiting"
INSTALL_MOBILE_SDK_ARG="--install-mobile-sdk"
HELP_ARG="--help"


# Get All arguments to ARGS variable
ARGS=("$@")

# HELP_ARG: Will show all the commands available for this SH.
HELP=$([[ " ${ARGS[@]} " =~ " $HELP_ARG " ]] && echo true || echo false)

# SKIP_WAITING_ARG: Will not keep the shell open after the script finishes running.
SKIP_WAITING=$([[ " ${ARGS[@]} " =~ " $SKIP_WAITING_ARG " ]] && echo true || echo false)

# INSTAL_SDK_ARG: Will install all the Mobile SDK dependencies
INSTALL_MOBILE_SDK=$([[ " ${ARGS[@]} " =~ " $INSTALL_MOBILE_SDK_ARG " ]] && echo true || echo false)

if [ $HELP == "true" ]; then
  echo "    $CLEAN_SANDOBOX_ARG: Will clean up all the sandboxes"
  echo "    $SKIP_WAITING_ARG: Will not keep the shell open after the script finishes running."
  echo "    $INSTALL_MOBILE_SDK_ARG: Will install all the Mobile SDK dependencies"
  return 1;
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

# Restore microservice
cd "Microservices" || exit 
dotnet restore
cd ..


# Check if the user is running as Administrator
net session > /dev/null 2>&1

if [ $? -eq 0 ] && [ $INSTALL_MOBILE_SDK = "true" ]; then
    
    if [ $INSTALL_MOBILE_SDK = 'true' ] && [ $UPROJECT_PATH ]; then
      echo "INSTALLING MOBILE SDK"
      # Extract the version directly from the .uproject file using grep and sed
      ENGINE_VERSION=$(grep -o '"EngineVersion": *"[^"]*"' "$UPROJECT_PATH" | sed -E 's/.*"EngineVersion": *"([^"]+)".*/\1/')

      # If EngineVersion is not found, try to get EngineAssociation
      if [ -z "$ENGINE_VERSION" ]; then
          ENGINE_VERSION=$(grep -o '"EngineAssociation": *"[^"]*"' "$UPROJECT_PATH" | sed -E 's/.*"EngineAssociation": *"([^"]+)".*/\1/')
      fi

      # If neither EngineVersion nor EngineAssociation is found, set to unknown
      if [ -z "$ENGINE_VERSION" ]; then
          ENGINE_VERSION="unkown"
      fi

      echo "ENGINE VERSION $ENGINE_VERSION"

      if ! [ $ENGINE_VERSION = 'unknown' ]; then

        KEY="HKLM\\SOFTWARE\\EpicGames\\Unreal Engine\\${ENGINE_VERSION}"
       
        ENGINE_PATH=$(reg query "$KEY" | awk -F'    ' '/InstalledDirectory/ {print $NF}')

        if [ -z "$ENGINE_PATH" ]; then
            echo "Unreal Engine $ENGINE_VERSION not found in registry."
        else
            echo "Unreal Engine $ENGINE_VERSION is installed at: $ENGINE_PATH"
        fi

        # Check if the engine path exists
        if [ -d "$ENGINE_PATH" ]; then
              
              BAT_PATH_FILE="${ENGINE_PATH}\\Engine\\Build\\BatchFiles\\RunUAT.bat"

              output=$(start cmd.exe //k " "${BAT_PATH_FILE}" Turnkey -Command=InstallSDK Platform=Android")
        else
              echo "Engine version $ENGINE_VERSION not found in expected locations."
        fi
      fi
    fi
else 
  if [ $INSTALL_MOBILE_SDK = "true" ]; then
    echo "WARNING: You are NOT running as Administrator! It's required to SDK install."
  fi
fi

if ! command -v dotnet >/dev/null 2>&1; then
    echo ".NET is not installed."
    return 1
fi

# Verify that the dotnet tool is callable by listing installed tools
if ! dotnet tool list >/dev/null 2>&1; then
    echo "The dotnet tool cannot be called, which may indicate a misconfiguration. Make sure that Dotnet SDK is installed."
    return 1
fi


if [ $SKIP_WAITING = 'false' ]; then
  echo "Prepare Repo finished executing. Press any key to exit."
  read -r
else
  echo "Prepare Repo finished executing"
fi