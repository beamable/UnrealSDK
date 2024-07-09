#!/bin/bash

PATH_TO_UNREAL_SDK_REPO=$1
INSTALL_OSS=${2:-false}

if [ "$PATH_TO_UNREAL_SDK_REPO" == "" ]; then
    echo "Please provide the path to the folder on your machine that contains the Beamable Unreal SDK."
    return 1
fi

if [ ! -d "$PATH_TO_UNREAL_SDK_REPO"  ]; then
    echo "The provided path doesn't exist."
    return 1
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

# Install the SDK in your project
# Find the .uproject file path and name
UPROJECT_PATH=$(find . -name "*.uproject" -print -quit)
echo "Found .uproject: $UPROJECT_PATH"
UPROJECT_NAME=$(basename "$UPROJECT_PATH" ".uproject")
echo "Installing the SDK in your project: $UPROJECT_NAME"

# Ensure we are inside a unreal project root folder.
if [ $UPROJECT_PATH == "" ]; then
   echo "Please run this script from inside a folder containing a .uproject (your Unreal Project's root)."
   return 1
fi

# Check for .beamable directory
if [ ! -d ".beamable" ]; then
   echo ".beamable folder not found. Creating one here."
   mkdir .beamable
fi

if [ ! -f ".config/dotnet-tools.json" ]; then
    dotnet new tool-manifest
fi

# Read out the expected version of the CLI
CLI_VERSION=0.0.123

# Install Beamable.Tools with optional version
dotnet tool install Beamable.Tools --version "$CLI_VERSION"
echo "Beamable Tools are installed. To call them use \"dotnet beam\" from any directory under your Unreal project root."

dotnet beam unreal init "$PATH_TO_UNREAL_SDK_REPO" "$UPROJECT_PATH" "$INSTALL_OSS"
echo "Installed Beamable SDK successfully."
