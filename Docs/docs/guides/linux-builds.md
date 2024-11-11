<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

# Linux Builds workflow

This guide will provide a way to get a working Linux build on Windows.

!!! info "Building from Docker"
	While it is possible to build game using a Docker, we found that solution suboptimal compared to the one described in this guide.
    
## Cross Compilation

!!! warning "Windows only"
	Cross-compiling in Unreal world is limited to **Windows** only. On Linux you can compile only Linux target, same for Mac users.

In order to get cross compilation to work it requires:
1. Go to [Unreal docs](https://dev.epicgames.com/documentation/en-us/unreal-engine/linux-development-requirements-for-unreal-engine?application_version=5.3#versionhistory) page that contains toolchains, download and install the `Cross-Compile Toolchain` that matches version of Unreal Engine you are using.
2. Update environment variables by adding new variable `LINUX_MULTIARCH_ROOT` with value being the path to the newly installed toolchain. It should be something like `F:\UnrealToolchains\v22_clang-16.0.6-centos7`.
3. Now when game is open in editor it should be possible to build for the `Linux` Target platform:

![](./images/linux-builds-editor.png#center)

## Testing the build

In order to test Linux game builds using other machine with Linux installed is recommended. 
For the server ones it is easy to test them on Windows machine in two different ways.

### WSL 

[WSL](https://learn.microsoft.com/en-us/windows/wsl/about) is a feature of Windows for running a Linux environment on Windows machine, without Docker.

!!! note Assumption
    This part of tutorial is written with assumption that WSL is installed and operational.

1. Build Linux Server target build of the game.
2. Open `Windows Subsystem for Linux` console in `LinuxServer` directory of the build. Directory should contain `Engine` directory, directory with the same name as the project and a script file with filename in format: `{ProjectName}Server.sh`.
3. Run the script file: `./{ProjectName}Server.sh`.
4. Server should run.

### Docker

Using Docker for running already builded server builds is often used to provide a server builds to server providers.
Beamable does provide a working example of that workflow in [Hathora Sample](../samples/complex/hathora-demo.md).

!!! note Assumption
    This part of tutorial is written with assumption that Docker is installed and operational.

1. Build Linux Server target build of the game.
2. Open `LinuxServer` directory of the build. Directory should contain `Engine` directory, directory with the same name as the project and a script file with filename in format: `{ProjectName}Server.sh`.
3. Create `Dockerfile` file in `LinuxServer` directory. Copy the text from below into it, while updating the paths to match the builded project:
```dockerfile
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

RUN chmod +x {ProjectName}Server.sh
RUN chmod +x {ProjectName}/Binaries/Linux/{ProjectName}Server

# Expose the Unreal game server port
EXPOSE 7777/udp

# Start init script (passing any parameters you need)
ENTRYPOINT [ "./{ProjectName}Server.sh", "-custom_parameter=SOME_VALUE" ]
```
4. Open command line in `LinuxServer` directory and run this command: `docker build -t my_server .`.
5. Now it is possible to run the server build with command: `docker run -t my_server`.
