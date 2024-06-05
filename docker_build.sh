#!/bin/sh

docker pull ghcr.io/epicgames/unreal-engine:dev-5.3.2

argument=${1:-"client"}
argument_two=${2:-""}

if [ $argument = "server" ]; then
    echo "Building server"
    docker build --build-arg BUILD_TYPE=-server --progress plain -t unrealrunner .
else
    echo "Building client"
    docker build --progress plain -t unrealrunner .
fi

docker run --name unreal_container -d unrealrunner:latest
docker cp unreal_container:/home/ue4/PackagedProject .

if [ $argument_two = "cache" ]; then
    echo "Copying Intermediate and Saved directories from container"
    docker cp unreal_container:/home/ue4/project/Intermediate .
    docker cp unreal_container:/home/ue4/project/Saved .
fi

docker stop unreal_container
docker rm unreal_container

if [ $argument = "server" ]; then
    cp Plugins/BEAMPROJ_HathoraDemo/Dockerfile PackagedProject/LinuxServer/Dockerfile
fi
