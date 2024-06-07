
# Internal command used by the Windows docker image

Set-Item -Path "Env:\UE_SELF_BUILT" -Value "1" -Force
$parentDirectory = Split-Path $MyInvocation.MyCommand.Path -Parent

$unrealPath = "C:\UnrealEngine\Engine"

& "${unrealPath}\Binaries\ThirdParty\DotNet\6.0.302\windows\dotnet.exe" `
 "${unrealPath}\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll" `
 -ProjectFiles -UsePrecompiled -Game "${parentDirectory}/BeamableUnreal.uproject"
& "${unrealPath}\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="${parentDirectory}\BeamableUnreal.uproject" `
 -utf8output `
 -platform=Win64 `
 -clientconfig=%CLIENT_CONFIG% `
 -serverconfig=%SERVER_CONFIG% %BUILD_ARG% `
 -noP4 -nodebuginfo %MAP_ARG% `
 -cook -build -stage -prereqs -pak -archive `
 -archivedirectory=C:\PackagedProject