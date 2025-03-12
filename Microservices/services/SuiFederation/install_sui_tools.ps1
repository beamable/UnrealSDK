# Define the container name and image
$containerName = "temp_sui_tools"
$imageName = "mysten/sui-tools:ci"
$targetFile = "/usr/local/bin/sui"
$destinationPath = "SuiTools"

# Check if Docker is installed
if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
    Write-Host "Docker is not installed or not found in PATH. Please install Docker first." -ForegroundColor Red
    exit 1
}

# Step 1: Create a temporary container
Write-Host "Creating temporary container from image $imageName..."
docker create --name $containerName $imageName | Out-Null

# Step 2: Copy the sui binary from the container to the local machine
Write-Host "Extracting $targetFile from $containerName..."
docker cp "$containerName`:$targetFile" $destinationPath

# Step 3: Remove the temporary container
Write-Host "Removing temporary container..."
docker rm $containerName | Out-Null

Write-Host "Extraction complete! The file has been saved as: $destinationPath" -ForegroundColor Green