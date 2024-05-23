FROM ghcr.io/epicgames/unreal-engine:dev-5.3.2 as builder

USER ue4
# use --build-arg BUILD_TYPE=-server in docker build to set it to be server build
ARG BUILD_TYPE=" "

# by default it passes all maps, you can pass value `--build-arg MAP_ARG=-map=DefaultMap+BeamBackendTests` to override it
ARG MAP_ARG=-allmaps
ARG CLIENT_CONFIG=Shipping
ARG SERVER_CONFIG=Shipping

# Copy your Unreal project files into the Docker image
COPY --chown=ue4 . /home/ue4/project

RUN /home/ue4/UnrealEngine/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet /home/ue4/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll -ProjectFiles -UsePrecompiled -Game "/home/ue4/project/BeamableUnreal.uproject"

RUN /home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project=/home/ue4/project/BeamableUnreal.uproject \
-utf8output \
-platform=Linux \
-clientconfig=$CLIENT_CONFIG \
-serverconfig=$SERVER_CONFIG \
 $BUILD_TYPE \
-noP4 -nodebuginfo $MAP_ARG \
-cook -build -pak -archive \
-stage -prereqs \
-archivedirectory=/home/ue4/PackagedProject || cat /home/ue4/Library/Logs/Unre*gine/LocalBuildLogs/UBT-.txt
