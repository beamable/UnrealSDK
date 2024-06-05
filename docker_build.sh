#!/bin/sh

docker pull ghcr.io/epicgames/unreal-engine:dev-5.3.2

argument=${1:-"nothing"}
if [ $argument = "server" ]; then
    docker build --build-arg BUILD_TYPE=-server --progress plain -t unrealrunner .
else
    docker build --progress plain -t unrealrunner .
fi

docker run --name unreal_container -d unrealrunner:latest
docker cp unreal_container:/home/ue4/PackagedProject .

argument_two=${2:-"nothing"}
if [ $argument_two = "copy_build" ]; then
    echo "Copying Intermediate and Saved directories from container"
    docker cp unreal_container:/home/ue4/Intermediate .
    docker cp unreal_container:/home/ue4/Saved .
fi

docker stop unreal_container
docker rm unreal_container

if [ $argument = "server" ]; then
    cp Plugins/BEAMPROJ_HathoraDemo/Dockerfile PackagedProject/LinuxServer/Dockerfile
fi
