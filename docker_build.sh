#!/bin/sh

docker pull ghcr.io/epicgames/unreal-engine:dev-5.3.2

argument=${1:-"nothing"}
if [ $argument = "server" ]; then
    docker build --build-arg BUILD_TYPE=-server --build-arg --progress plain -t unrealrunner .
else
    docker build --build-arg --progress plain -t unrealrunner .
fi

docker run --name unreal_container -d unrealrunner:latest
docker cp unreal_container:/home/ue4/PackagedProject .
docker stop unreal_container
docker rm unreal_container

if [ $argument = "server" ]; then
    cp Plugins/BEAMPROJ_HathoraDemo/Dockerfile PackagedProject/LinuxServer/Dockerfile
fi
