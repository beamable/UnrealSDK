
/home/ue4/UnrealEngine/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet /home/ue4/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll -ProjectFiles -UsePrecompiled -Game "/home/ue4/project/BeamableUnreal.uproject"
/home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project=/home/ue4/project/BeamableUnreal.uproject \
-utf8output \
-platform=Linux \
-clientconfig=$CLIENT_CONFIG \
-serverconfig=$SERVER_CONFIG \
 $BUILD_TYPE \
-noP4 -nodebuginfo $MAP_ARG \
-cook -build -pak -archive \
-stage -prereqs \
-archivedirectory=/home/ue4/PackagedProject || cat /home/ue4/Library/Logs/Unre*gine/LocalBuildLogs/UBT-.txt