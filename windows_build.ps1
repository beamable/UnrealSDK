$buildType = $args[0]

# Check if BeamProjOverride.txt exists and is not empty
if (Test-Path "BeamProjOverride.txt") {
    $content = Get-Content "BeamProjOverride.txt" | Out-String
    if ($content.Trim()) {
        $projectId = $content.Trim()
    } else {
        $projectId = "BEAMPROJ_Sandbox"
    }
} else {
    $projectId = "BEAMPROJ_Sandbox"
}
Set-Content  -Path "BeamProjOverride.txt" -Value $projectId
$unrealPath = $Env:UNREAL_ENGINE_PATH

if ([string]::IsNullOrEmpty($Env:UNREAL_ENGINE_PATH)) {
    $unrealPath = "C:\Users\Administrator\Documents\Git\UnrealEngine\Engine"
}
Write-Output "Engine path: $unrealPath"
$extraArg = ""
if ($buildType -eq 'server') {
    $extraArg = "-server"
}

Set-Item -Path "Env:\UE_SELF_BUILT" -Value "1" -Force
$parentDirectory = Split-Path $MyInvocation.MyCommand.Path -Parent

& "${unrealPath}\Binaries\ThirdParty\DotNet\6.0.302\windows\dotnet.exe" `
 "${unrealPath}\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll" `
 -ProjectFiles -UsePrecompiled -Game "${parentDirectory}/BeamableUnreal.uproject"

& "${unrealPath}\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="${parentDirectory}\BeamableUnreal.uproject" `
 -utf8output `
 -platform=Win64 `
 -clientconfig=Shipping `
 -serverconfig=Shipping `
 "${extraArg}" `
 -noP4 -nodebuginfo -allmaps `
 -cook -build -stage -prereqs -pak -archive `
 -archivedirectory=${parentDirectory}\PackagedProject
