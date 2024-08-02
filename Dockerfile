FROM ghcr.io/epicgames/unreal-engine:dev-5.4.2 as builder

USER ue4
# use --build-arg BUILD_TYPE=-server in docker build to set it to be server build
ARG BUILD_TYPE=" "
ENV BUILD_ARG=${BUILD_TYPE}
# by default it passes all maps, you can pass value `--build-arg MAP_ARG=-map=DefaultMap+BeamBackendTests` to override it
ARG MAP_ARG=-allmaps
ENV MAP_ARG=${MAP_ARG}
ENV CLIENT_CONFIG=${CLIENT_CONFIG}
ARG SERVER_CONFIG=Shipping
ENV SERVER_CONFIG=${SERVER_CONFIG}
ENV UE_SELF_BUILT="0"

CMD ["bash", "/home/ue4/project/docker_cmd_linux.sh" ]