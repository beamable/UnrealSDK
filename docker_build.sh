#!/bin/sh

docker pull ghcr.io/epicgames/unreal-engine:dev-5.3.2

if [ -s "BeamProjOverride.txt" ]; then
    project_id=$(<"BeamProjOverride.txt")
else
    project_id="BEAMPROJ_Sandbox"
fi

argument=${1:-"client"}
argument_two=${2:-""}
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

docker run --name unreal_container -d $image_name:latest
docker cp unreal_container:/home/ue4/PackagedProject .

if [ $argument_two = "cache" ]; then
    echo "Copying Intermediate and Saved directories from container"
    ls -l
    docker cp unreal_container:/home/ue4/project/Intermediate .
    docker cp unreal_container:/home/ue4/project/Saved .
    ls -l
fi

docker stop unreal_container
docker rm unreal_container

if [ $argument = "server" ]; then
    cp Plugins/BEAMPROJ_HathoraDemo/Dockerfile PackagedProject/LinuxServer/Dockerfile
fi
