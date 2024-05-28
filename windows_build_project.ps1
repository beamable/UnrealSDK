$buildType = $args[0]

docker image prune

if ($buildType -eq 'server') {
    docker build --build-arg BUILD_TYPE=-server -t unreal-win64-project -f WinDockerfile .
} else {
    docker build -t unreal-win64-project -f WinDockerfile .
}
docker run --name unreal-project -d unreal-win64-project
docker cp unreal-project:C:\Project\PackagedProject .
docker stop unreal-project
docker rm unreal-project

$artifacts_exists = Test-Path PackagedProject -PathType Container;

if (!$artifacts_exists) {
    exit 1
}
