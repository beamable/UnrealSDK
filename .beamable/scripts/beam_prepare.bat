@echo off
dotnet --version >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo .NET is not installed.
    exit /b 1
)

REM Check for .beamable directory
if not exist .beamable\ (
    echo This script must be run from a directory containing the .beamable directory.
    exit /b 1
)

REM Check for the dotnet-tools.json file in the .config directory
if not exist .config\dotnet-tools.json (
    dotnet new tool-manifest
)

REM Install Beamable.Tools with optional version
if "%1"=="" (
    dotnet tool install Beamable.Tools
) else (
    dotnet tool install Beamable.Tools --version %1
)

echo Beamable Tools are installed. To call them use `dotnet beam`. 