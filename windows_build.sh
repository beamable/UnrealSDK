#!/bin/bash

buildType=${1:-"client"}
platform=${2:-"Win64"}
unrealPath=${3:-${UNREAL_ENGINE_PATH:-"C:/Users/Administrator/Documents/Git/UnrealEngine/Engine"}}

extraArgs=""
if [ "$buildType" == "server" ]; then
    extraArgs="-server -serverconfig=Shipping"
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
    -utf8output \
    -platform="${platform}" \
    "$extraArgs" \
    -noP4 -nodebuginfo -allmaps \
    -cook -build -stage -prereqs -pak -archive \
    -archivedirectory="${archiveDir}"

if [[ "$buildType" == "server" && "$projectId" == "BEAMPROJ_HathoraDemo" && "$platform" == "Linux" ]]; then
    cp ${parentDirectory}/Plugins/BEAMPROJ_HathoraDemo/Dockerfile ${archiveDir}/LinuxServer/Dockerfile
    docker build -t hathora_server ${archiveDir}/LinuxServer
fi
