#!/bin/sh

# Verify that dotnet is installed
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

BASEDIR=$(pwd)
echo "$BASEDIR"
cd $BASEDIR

SANDBOX_PROJ_NAME="BEAMPROJ_Sandbox"
PLUGIN_SANDBOX_PATH="$(pwd)/Plugins/$SANDBOX_PROJ_NAME"
TEMPLATE_SANDBOX_PATH="$(pwd)/Templates/Plugins/$SANDBOX_PROJ_NAME"

if [ ! -d "Microservices/services/MSPlayground" ]; then
    echo "Creating BEAMPROJ_Sandbox Plugin"
    mkdir -p "$PLUGIN_SANDBOX_PATH"
    cp -r "$TEMPLATE_SANDBOX_PATH"/* "$PLUGIN_SANDBOX_PATH"
fi

# Check if the beam CLI is installed globally
if ! command -v beam >/dev/null 2>&1; then
    dotnet tool install Beamable.Tools --global --version 2.0.2 --allow-downgrade 
else
    dotnet tool update Beamable.Tools --global --version 2.0.2 --allow-downgrade    
fi

# Create a microservice
if [ ! -d "Microservices/services/MSPlayground" ]; then
    echo "Creating MSPlayground microservice for local development."
    beam project new service MSPlayground --sln "Microservices/Microservices.sln"
fi

# Create a microstorage
if [ ! -d "Microservices/services/DBPlayground" ]; then
    echo "Creating DBPlayground storage for local development."
    beam project new storage DBPlayground --sln "Microservices/Microservices.sln" --link-to MSPlayground
fi