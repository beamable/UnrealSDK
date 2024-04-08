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

# Check for .beamable directory
if [ ! -d ".beamable" ]; then
    echo "This script must be run from a directory containing the .beamable directory."
    exit 1
fi

if [ ! -f ".config/dotnet-tools.json" ]; then
    dotnet new tool-manifest
fi

# Install Beamable.Tools with optional version
if [ -z "$1" ]; then
    dotnet tool install Beamable.Tools
else
    dotnet tool install Beamable.Tools --version "$1"
fi

echo "Beamable Tools are installed. To call them use `dotnet beam`."