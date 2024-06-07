#!/bin/sh

# Internal command used by the Linux docker image

echo "GENERATE PROJECT"
/home/ue4/UnrealEngine/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet /home/ue4/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll -ProjectFiles -UsePrecompiled -Game "/home/ue4/project/BeamableUnreal.uproject"

echo "START BUILD ${BUILD_ARG}"
/home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project=/home/ue4/project/BeamableUnreal.uproject \
-utf8output \
-platform=Linux \
-clientconfig=$CLIENT_CONFIG \
-serverconfig=$SERVER_CONFIG \
 $BUILD_ARG -noP4 -nodebuginfo $MAP_ARG -cook -build -stage -prereqs -pak -archive -archivedirectory=/home/ue4/packaged || cat /home/ue4/Library/Logs/Unre*gine/LocalBuildLogs/UBT-.txt
echo "BUILD COMPLETED"