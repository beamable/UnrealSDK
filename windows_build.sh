#!/bin/bash

buildType=${1:-"client"}
platform=${2:-"Win64"}
extraArg=""
if [ "$buildType" == "server" ]; then
    extraArg="-server"
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

unrealPath="${UNREAL_ENGINE_PATH}"

if [ -z "$UNREAL_ENGINE_PATH" ]; then
    unrealPath="C:/Users/Administrator/Documents/Git/UnrealEngine/Engine"
fi

export UE_SELF_BUILT=1
if command -v cygpath >/dev/null 2>&1; then
    parentDirectory=$(cygpath -da "$(dirname "$0")")
else
    parentDirectory=$(realpath "$0")
fi
archiveDir="${parentDirectory}/PackagedProject"
echo "Starting a $projectId $buildType build for $platform platform."

"${unrealPath}/Binaries/ThirdParty/DotNet/6.0.302/windows/dotnet.exe" \
    "${unrealPath}/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll" \
    -ProjectFiles -UsePrecompiled -Game "${parentDirectory}/BeamableUnreal.uproject"
"${unrealPath}/Build/BatchFiles/RunUAT.bat" BuildCookRun -project="${parentDirectory}/BeamableUnreal.uproject" \
    -utf8output \
    -platform="${platform}" \
    "$extraArg" \
    -noP4 -nodebuginfo -allmaps \
    -cook -build -stage -prereqs -pak -archive \
    -archivedirectory="${archiveDir}"