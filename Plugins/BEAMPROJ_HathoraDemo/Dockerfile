FROM ubuntu:22.04

# Add these dependencies to enable your server to make outbound TLS requests
RUN apt-get update && \
    apt-get install -y ca-certificates && \
    update-ca-certificates

RUN groupadd --gid 1000 unreal \
  && useradd --uid 1000 --gid unreal --create-home unreal
USER unreal

# Copy the Unreal game server contents
WORKDIR /home/unreal
COPY --chown=unreal:unreal . .

RUN chmod +x BeamableUnrealServer.sh
RUN chmod +x BeamableUnreal/Binaries/Linux/BeamableUnrealServer

# Expose the Unreal game server port
EXPOSE 7777/udp

# Start init script (passing any parameters you need)
ENTRYPOINT [ "./BeamableUnrealServer.sh", "-hostname=$HATHORA_PROCESS_ID" ]
