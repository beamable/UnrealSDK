ARG UE_IMAGE_TAG=dev-5.6.1
# First image is used to build your project inside a container
FROM ghcr.io/epicgames/unreal-engine:${UE_IMAGE_TAG} AS builder

# Copy source code
COPY --chown=ue4:ue4 . /tmp/project

# Define the build args with a default
ARG SERVER_CONFIG=Development
ARG PROJECT_FILE_NAME=ProjectName
ARG UE_BUILD_ARGS

# Clean & build dedicated server for Linux
RUN /home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun \
    -serverconfig=${SERVER_CONFIG} \
    -project=/tmp/project/${PROJECT_FILE_NAME}.uproject \
    -utf8output -nodebuginfo -allmaps -noP4 -cook -ddc=NoZenLocalFallback -build -stage -prereqs -pak -package -archive \
    -archivedirectory=/tmp/project/Packaged \
    -platform=Linux -server -noclient \
    ${UE_BUILD_ARGS}

# Second image is used to run the project build
FROM ubuntu:22.04 AS runtime

ARG INSTALL_STEAMCLIENT=false
ARG BUILD_TARGET_FILE_NAME=TargetFileName

ENV TARGET_FILE_NAME=${BUILD_TARGET_FILE_NAME}

# Specify container command for later (main process)
CMD ["/home/ue4/project/StartServer.sh"]

# Install runtime dependencies
RUN apt-get update && \
    apt-get install jq curl -y && \
    apt-get clean && \
    rm -rf /var/lib/{apt,dpkg,cache,log}/

# Create User
RUN useradd ue4

# Copy build and runtime files in the runtime container
COPY ./.edgegap-unreal-buildutils/StartServer.sh /home/ue4/project/StartServer.sh
RUN sed -i 's/\r$//' /home/ue4/project/StartServer.sh
COPY --from=builder --chown=ue4:ue4 /tmp/project/Packaged/LinuxServer /home/ue4/project

# Single RUN with conditional
RUN if [ "${INSTALL_STEAMCLIENT}" = "true" ]; then \
      mkdir -p /home/ubuntu/.steam/sdk64 && \
      curl -L -o /home/ubuntu/.steam/sdk64/steamclient.so "https://github.com/edgegap/edgegap-unreal-buildutils/raw/refs/heads/main/steamclient.so" && \
      chmod 755 /home/ubuntu/.steam/sdk64/steamclient.so; \
    fi

USER ue4

# Expose UDP port
EXPOSE 7777/udp

