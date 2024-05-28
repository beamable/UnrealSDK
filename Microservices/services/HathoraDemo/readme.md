## Requirements and Assumptions
This project requires the following tools to be installed.
1. [Dotnet (6.0 or later)](https://dotnet.microsoft.com/en-us/download)
2. [Docker](https://www.docker.com/products/docker-desktop/)

This project assumes that you are using [Git](https://git-scm.com/) for version control. 
A `.gitignore` file is included, but if you are using a different version control system, you 
must create a custom ignore-file.

// TODO: What happens if you create template directly with `dotnet new` instead of using `beam project new`


## Getting Started
Before you begin, you'll need to create a Beamable organization.
You can create a Beamable organization through the Unity Editor, or online at [Beamable.com](https://beta-portal.beamable.com/signup/registration/).

Here is the expected file structure.
```
/project
  project.sln
  /.beamable
     .config-defaults.json
     .linkedProjects.json
     .beamoLocalManifest.json
     .beamoLocalRuntime.json
  /services
     /HathoraDemo
        HathoraDemo.csproj
        Dockerfile
        Program.cs
        HathoraDemo.cs
     /HathoraDemoLibrary
        HathoraDemoLibrary.csproj
        HathoraDemoLibrary.cs
```

## Running Locally
The HathoraDemo project can be run locally by starting it from an IDE, or by executing the `dotnet run` command.
When a Microservice is built, a web-page will be opened automatically directed to the local swagger documentation for the service.

The project may also be run in Docker by executing the following command. However, it is recommended to 
run the dotnet process locally for workflow speed. 
```shell
beam services deploy --ids HathoraDemo
```

### MSBuild Properties
The `HathoraDemo.csproj` file has a few configuration options that can be set.
```xml
<PropertyGroup>
    <!-- The tool path for the beamCLI. "dotnet beam" will refer to the local project tool, and "beam" would install to a globally installed tool -->
    <BeamableTool>dotnet beam</BeamableTool>

    <!-- When "true", this will auto-generate client code to any linked unity projects -->
    <GenerateClientCode>true</GenerateClientCode>
</PropertyGroup>
```

#### BeamableTool
By default, both HathoraDemo and HathoraDemoLibrary have the BeamCLI installed as a project tool. 
However, it is likely that `beam` is installed as a global tool, and as such, the `BeamableTool` value
could be changed `beam`.

### Connecting to a Unity Project
The project can be linked to a number of Unity Projects. The `./beamable/.linkedProjects.json` file 
contains the relative paths to linked Unity Projects. You can add an association by editing that file, 
or by executing
```shell
beam project add-unity-project .
```

When the project is built, the `generate-client` msbuild target will generate a C# client file
at each linked Unity project's `Assets/Beamable/Microservice/Microservices/HathoraDemoClient.cs`. 

Additionally, the `share-code` msbuild target in the HathoraDemoLibrary project will copy their
built `.dll` files into the `Assets/Beamable/Microservices/CommonDlls` directory. Unity will be able
to share the `.dll` files meant for the shared library. 

### Limitations

## Deploying
The project can be deployed to the remote realm by running the follow command. 
```shell
beam services ps --remote
beam services deploy --remote
```

However, the realm that is used will depend on the current value of the beam CLI. The current value
can be viewed by inspecting the `./beamable/.config-defaults.json` file, or by running the following
command.
```shell
beam config
```

If the CLI is not authenticated, then you must log in and pass the `--saveToFile` flag. Otherwise, 
you will need to add the `--refresh-token` option to the `beam services` commands. 
```shell
beam login --saveToFile
```