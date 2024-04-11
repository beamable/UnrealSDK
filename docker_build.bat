docker pull ghcr.io/epicgames/unreal-engine:dev-5.3.2

IF "%1"=="server" ( 
    docker build --build-arg BUILD_TYPE=-server --build-arg MAP_ARG=-map=DefaultMap+BeamBackendTests --progress plain -t unrealrunner .
) ELSE (
    docker build --build-arg MAP_ARG=-map=DefaultMap+BeamBackendTests --progress plain -t unrealrunner .
)
docker run --name unreal_container -d beamable-unreal-client:latest
docker cp unreal_container:/home/ue4/PackagedProject .
docker stop unreal_container
docker rm unreal_container
