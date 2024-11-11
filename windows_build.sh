#!/bin/bash

buildType=${1:-"client"}
platform=${2:-"Win64"}
unrealPath=${3:-${UNREAL_ENGINE_PATH:-"C:/Users/Administrator/Documents/Git/UnrealEngine/Engine"}}

extraArgs=""
if [ "$buildType" == "server" ]; then
    extraArgs="-server"
    
    if [ -z "$LINUX_MULTIARCH_ROOT" ] || [ ! -d "$LINUX_MULTIARCH_ROOT" ]; then
        export LINUX_MULTIARCH_ROOT="C:\UnrealToolchains\v22_clang-16.0.6-centos7"
        echo "Environment variable LINUX_MULTIARCH_ROOT set to: $LINUX_MULTIARCH_ROOT"
    else
        echo "Environment variable LINUX_MULTIARCH_ROOT already exists and is valid: $LINUX_MULTIARCH_ROOT"
    fi
fi

# Check if BeamProjOverride.txt exists and is not empty
if [ -f "BeamProjOverride.txt" ]; then
    content=$(<BeamProjOverride.txt)
    if [ -n "$content" ]; then
        projectId=$(echo "$content" | xargs)
    else
        projectId="BEAMPROJ_Sandbox"
    fi
else
    projectId="BEAMPROJ_Sandbox"
fi

echo "$projectId" > BeamProjOverride.txt

export UE_SELF_BUILT=1

if command -v cygpath >/dev/null 2>&1; then
    parentDirectory=$(cygpath -da "$(dirname "$0")")
else
    parentDirectory=$(realpath "$0")
fi
archiveDir="${parentDirectory}/PackagedProject"
echo "Starting a $projectId $buildType build for $platform platform"

rm -rf Plugins/Developer/RiderLink

"${unrealPath}/Binaries/ThirdParty/DotNet/6.0.302/windows/dotnet.exe" \
    "${unrealPath}/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll" \
    -ProjectFiles -UsePrecompiled -Game "${parentDirectory}/BeamableUnreal.uproject"
"${unrealPath}/Build/BatchFiles/RunUAT.bat" BuildCookRun -project="${parentDirectory}/BeamableUnreal.uproject" \
    -platform="${platform}" \
    "$extraArgs" \
    -noP4 -nodebuginfo -package -allmaps \
    -cook -build -stage -prereqs -archive \
    -archivedirectory="${archiveDir}"

# disabled for now
# if [[ "$buildType" == "server" && "$projectId" == "BEAMPROJ_HathoraDemo" && "$platform" == "Linux" ]]; then
#     cp ${parentDirectory}/Plugins/BEAMPROJ_HathoraDemo/Dockerfile ${archiveDir}/LinuxServer/Dockerfile
#     docker build -t hathora_server ${archiveDir}/LinuxServer
# fi
