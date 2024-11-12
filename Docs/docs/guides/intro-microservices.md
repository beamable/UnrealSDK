# Getting Started with C# Microservices
To get started with Microservices in your project, you need a couple of things:

- Most Unreal `.[vcs]ignore` file templates will ignore all `*.sln` files. Instead of doing that, make sure to only ignore in the root directory with this  `/*.sln` instead of `*.sln`.
	- You can also just ensure your Microservice `.sln` is not ignored explicitly.
- Ensure you have the Beamable CLI installed.

Creating your first microservice will automatically create your solution for you. Following the guide below will generate the following recommended folder structure:

```
/repo-root
|- ProjectName.uproject
|- ProjectName.sln
|- ProjectNameBeamable/
|-- ProjectNameBeamable.sln
|-- services/
|---- MicroserviceName/
|------ MicroserviceName.csproj
```
### Create the Microservice Solution and Project
**Make sure the editor is not running before starting this guide.**

Open a terminal/shell at your project's root and run the following command to create a new project and add a new microservice.

```
dotnet beam project new service MicroserviceName --sln ProjectNameBeamable/ProjectNameBeamable.sln
```

 The created Microservice would look something like the example one below here.
 
```csharp
public class MSPlayground : Microservice  
{  
    [ClientCallable]  
    public int Add(int a, int b)  
    {
	    return a + b;  
    }
}
```

**Now that you have a microservice, you can compile it via your IDE.**

Afterwards, you can run the command below from your Game Project's root.

```
dotnet beam project add-unreal-project .
```
 
Linking a project informs our CLI where it should put generated C++ files for communicating with the Microservice from UE code. To generate the project files, run:

```bash
# Run manually whenever you make schema changes to `Callable` method signatures (or types used in them)
dotnet beam project generate-client ProjectNameBeamable/services/MicroserviceName/bin/path/to/built/dll
```

!!! warning "Automatic Code Generation & Limitations"
	You can also `<GenerateClientCode>true</GenerateClientCode>` in the `BeamableSettings` **Property Group** inside `MicroserviceName.csproj`; this will run the command on every re-build of the service DLL.
	
	The automatic code generation is in early experimental stages and might see breaking changes in the near-future. For this reason, it is currently disabled by default.

After the generating the client in your Unreal project, you can:

- Add the generated plugin (`ProjectNameMicroserviceClients`) to your `uproject` file and enable it.
- Add the relevant plugin's modules to your `Target.cs` files.
- Add `ProjectNameMicroserviceClients.AddMicroserviceClients(this)` line to your  `Build.cs` files.

Now, you're ready to write code that invokes the microservice.

Here's what that would look like:

```cpp 
// From inside any GameInstanceSubsystem, Actor or Component...

// Get the Generated API subsystem
const auto MsApi = GEngine->GetEngineSubsystem<UBeamMSPlaygroundApi>();  

// Create an instance of the generated Request object.
const auto Req = UMSPlaygroundAddRequest::Make(1, 2, GetTransientPackage(), {});  

// Declare the handler for the addition
const auto Handler = FOnMSPlaygroundAddFullResponse::CreateLambda([this](FMSPlaygroundAddFullResponse Resp)  
{  
    // If the request failed or we are retrying, we do nothing  
    if (Resp.State != RS_Success)  
       return;  
  
    // Otherwise, print the value 
    UE_LOG(LogTemp, Display, TEXT("Microservice Add: %d"), Resp.SuccessData->Value);
});  

// Make the request (the user slot will usually be the UBeamCoreSettings::GetOwnerPlayerSlot())
FBeamRequestContext Ctx;  
MsApi->CPP_Add(UserSlot, Req, Handler, Ctx, {}, this);
```

Take a look at the [Microservices docs](../concepts/microservices.md) for more information about where to go from here.

## Optional - Create a MicroStorage
MicroStorages are a Beamable feature that allows you, the Game-Maker, access to a MongoDB you can use to define your own custom persisted data formats to go along with your own custom microservice logic. 

This is a useful architectural alternative when making complex features that do not map well to the default cases of Beamable's own data-storing Managed Services (Stats, Inventory and CloudStorage).

To create a `MicroStorage`, run the command below.

```
beam project new storage StorageName --sln ProjectNameBeamable/ProjectNameBeamable.sln \
  --link-to MicroserviceName
```

This will add a `StorageName.csproj` project to the solution and reference that new project in the `MicroserviceName.csproj` file, making the code in the `StorageName` project accessible to the Microservice.

Storages ***cannot*** exist independent of Microservices and must be associated with one at all times. The `link-to` option will make the given Microservice depend on the newly created Storage. This dependency makes the storage accessible to the microservice.

!!! warning "Running Locally"
	MicroStorages require you to ALWAYS have docker running when running locally. Microservices that **DO NOT DEPEND** on storages can be run directly from the IDE without docker running at all. Microservices that **DO DEPEND** on storages can also be run from the IDE, but docker MUST be running too.

Take a look at this documentation for more information on how to write the code inside Storages and how to access them in Microservices.

## Optional - Libraries and C# Microservices
One of the big advantages of Beamable C# Microservices is that they are regular `.NET` projects. This means you get access to Nuget packages should you need to integrate Beamable with any particular Third-Party technology that we don't support out-of-the-box.

To do so, use Nuget to add a package dependency to a project (this can be done easily through any IDE --- or through `dotnet nuget` command pallet).

While definitely not the common case, it is possible for projects to require multiple services. When that happens, it is also common that those services share some logic or internal data types. To write your own code that is then shared between services:

- Create a `dll` project by running this command:
	- `beam project new common-lib LibraryName --sln ProjectNameBeamable/ProjectNameBeamable.sln`
- Adding a reference to it in any of your Microservice's `.csproj` files by adding this line to an **ItemGroup** block: 
	- `<ProjectReference Include="..\LibraryName\LibraryName.csproj"/>`

!!! warning "UE Code Generation Limitations"
	You can write any code here and share types between microservices. Keep in mind that, if you use these types in method signatures of multiple microservices, due to Unreal's lack of namespacing, you'll end up with two different UE types for the same shared type.
	
	For that reason, we currently recommend you do not expose shared complex types inside `Callable` method signatures.

