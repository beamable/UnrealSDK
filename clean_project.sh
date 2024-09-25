#!/bin/sh

set +v
BASEDIR=$(dirname "$0")
echo "$BASEDIR"
cd $BASEDIR
echo "* Clean Unreal Engine Project *"
echo ""
echo "Cleaning your project, please wait..."
# Use find to locate directories and remove them
for dir in Build Intermediate Saved DerivedDataCache PackagedProject; do
    find . -type d -name "$dir" -exec rm -rf {} +
done

rm BeamableUnreal.sln

echo ""
echo "Your project cleaned perfectly, you can generate Visual Studio project files now."
