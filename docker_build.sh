#!/bin/sh

docker pull ghcr.io/epicgames/unreal-engine:dev-5.3.2

if [ -s "BeamProjOverride.txt" ]; then
    project_id=$(<"BeamProjOverride.txt")
else
    project_id="BEAMPROJ_Sandbox"
fi

if [[ "$MSYSTEM" == "MINGW64" || "$MSYSTEM" == "MINGW32" ]]; then
  current_dir="$(pwd -W)"
else
  current_dir="$(pwd)"
fi

argument=${1:-"client"}
image_name="$argument"
image_name+="_"
image_name+="$project_id"
image_name="${image_name,,}"
echo "Resulting image: $image_name"

if [ $argument = "server" ]; then
    echo "Building server"
    docker build --build-arg BUILD_TYPE=-server --progress plain -t $image_name .
else
    echo "Building client"
    docker build --progress plain -t $image_name .
fi

docker stop unreal_container || true && docker rm unreal_container || true
docker run --name unreal_container -v $current_dir:/home/ue4/project $image_name:latest

docker cp unreal_container:/home/ue4/PackagedProject .

if [ $argument = "server" ]; then
    cp Plugins/BEAMPROJ_HathoraDemo/Dockerfile PackagedProject/LinuxServer/Dockerfile
fi
