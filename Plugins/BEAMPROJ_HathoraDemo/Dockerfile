FROM ubuntu:22.04
# Hathora sample server Dockerfile

# Add these dependencies to enable your server to make outbound TLS requests
RUN apt-get update && \
    apt-get install -y ca-certificates xdg-user-dirs && \
    update-ca-certificates

# Unreal doesn't like running as root, so let's create a user
RUN groupadd --gid 1000 unreal \
  && useradd --uid 1000 --gid unreal --create-home unreal
USER unreal

# Now copy over your server build
WORKDIR /home/unreal
COPY --chown=unreal:unreal . .

# Make sure your init script and server binary are executable
# If you have any other binaries (e.g. crash handlers), make sure to set those as executable too!

RUN chmod +x BeamableUnrealServer.sh
RUN chmod +x BeamableUnreal/Binaries/Linux/BeamableUnrealServer-Linux-Shipping
# Start init script (passing any parameters you need)
ENTRYPOINT [ "bash", "BeamableUnrealServer.sh" ]