#!/bin/bash

# Define the container name and image
container_name="temp_sui_tools"
image_name="mysten/sui-tools:ci"
target_file="/usr/local/bin/sui"
destination_path="SuiTools"

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo -e "\e[31mDocker is not installed or not found in PATH. Please install Docker first.\e[0m"
    exit 1
fi

# Step 1: Create a temporary container
echo "Creating temporary container from image $image_name..."
docker pull "$imageName"
docker create --name "$container_name" "$image_name" > /dev/null

# Step 2: Copy the sui binary from the container to the local machine
echo "Extracting $target_file from $container_name..."
docker cp "$container_name:$target_file" "$destination_path"

# Step 3: ZIP the SUI executable and delete
rm -f "$destinationPath/sui.zip"
zip "$destinationPath/sui.zip" "$destinationPath/sui"
rm -f "$destinationPath/sui"

# Step 4: Remove the temporary container
echo "Removing temporary container..."
docker rm "$container_name" > /dev/null

echo -e "\e[32mExtraction complete! The file has been saved as: $destination_path\e[0m"