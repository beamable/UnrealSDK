$buildType = $args[0]

# Check if BeamProjOverride.txt exists and is not empty
if (Test-Path "BeamProjOverride.txt") {
    $content = Get-Content "BeamProjOverride.txt" | Out-String
    if ($content.Trim()) {
        $project_id = $content.Trim()
    } else {
        $project_id = "BEAMPROJ_Sandbox"
    }
} else {
    $project_id = "BEAMPROJ_Sandbox"
}

# Get the first argument, default to "client" if not provided
$argument = if ($args.Count -ge 1) { $args[0] } else { "client" }

# Create the image name
$image_name = "${argument}_${project_id}_win64"

# Convert to lowercase
$image_name = $image_name.ToLower()

Write-Output "Resulting image: $image_name"
docker image prune

if ($buildType -eq 'server') {
    docker build --build-arg BUILD_TYPE=-server -t $image_name -f WinDockerfile .
} else {
    docker build -t $image_name -f WinDockerfile .
}
$parentDirectory = Split-Path $MyInvocation.MyCommand.Path -Parent

& docker run --name unreal-project -v "${parentDirectory}:C:\Project" "${image_name}:latest"

docker cp unreal-project:C:\PackagedProject .

docker stop unreal-project
docker rm unreal-project

$artifacts_exists = Test-Path PackagedProject -PathType Container;

if (!$artifacts_exists) {
    exit 1
}
