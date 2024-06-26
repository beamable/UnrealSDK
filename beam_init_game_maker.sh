#!/bin/bash

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
if [ ! -f "*.uproject" ]; then
   echo "Please run this script from inside a folder containing a .uproject (your Unreal Project's root)."
   exit 1
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


echo "Beamable Tools are installed. To call them use `dotnet beam` from any directory under your Unreal project root."