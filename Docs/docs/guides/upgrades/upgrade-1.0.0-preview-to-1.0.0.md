# 1.0.0-PREVIEW to 1.0.0

We highly recommend you start this process with no staged changes to your VCS and in an isolated local branch such that you can revert as needed.

- Download/Clone our Tagged Release.
  - Extract it to a location in the same drive as your project.
- Copy/Paste the `beam_game_maker_init.sh` into your project's root (next to your `.uproject` file).
- Open a shell (we recommend `GitBash` if you're using `git`) in your project root directory.
- Run that script passing in the path to our extracted project.

```shell
# If you just want to install the BeamableCore plugin (no OnlineSubsystem)
. beam_game_maker_init.sh "/e/Path/To/Unreal/SDK/Root/Folder"

# If you want to install OnlineSubsystemBeamable Plugin too (or had it installed).
. beam_game_maker_init.sh "/e/Path/To/Unreal/SDK/Root/Folder" true
```

!!! warning "Access Denied"
	   Unreal's integrations with various version control systems will sometimes make files Read-Only at the OS-level. If this is the case, you may see an `Access Denied` error when running the above script. Part of that script is deleting the old `Plugins/BeamableCore` folder and some of the `uasset`/`umap` files inside it might be flagged as read-only. To fix this, revert the changes, go to the `Plugins/BeamableCore`, and optionally `Plugins/OnlineSubsystemBeamable`, search for `uasset`/`umap` files and make them NOT read-only. On Windows, this can be done by the "Properties" panel of the file.
   
   Please contact our customer support if the above does not work.

If the script is successfull, you should see something like this:

```
Found .uproject: ./YourProject.uproject

Installing the SDK in your project: YourProject
Tool 'beamable.tools' is up to date (version '3.0.1' manifest file E:\Path\To\Your\.config\dotnet-tools.json) .
Beamable Tools are installed. To call them use "dotnet beam" from any directory under your Unreal project root.
Already installed BeamableCore plugin. Removing it so we can re-install it.
Installed BeamableCore plugin.

# If you're using OnlineSubsystemBeamable, you should see these lines...
Already installed OnlineSubsystemBeamable plugin. Removing it so we can re-install it.
Copying OnlineSubsystemBeamable plugin's Beamable Content folder.
Copying OnlineSubsystemBeamable plugin's Build.cs file.
Copying OnlineSubsystemBeamable plugin's Source/OnlineSubsystemBeamable/Beamable files.
Installed OnlineSubsystemBeamable plugin.

# This means that we successfully upgraded your CLI and SDK version
Installed Beamable SDK successfully.
```

Now, if you have microservices, do the following steps. If not, skip to the next section.

- Open a shell inside your project root and run: `dotnet tool restore`.
- Unlink the Unreal Project by deleting the `.beamable/linked-projects.json` file.
- Link it again using `dotnet beam project add-unreal-project .`
- Disable Automatic code Generation by setting `<GenerateClientCode>false</GenerateClientCode>` in every service's `csproj` file.        

- Follow the [CLI upgrade guide found here](https://docs.beamable.com/v2.0.0/docs/cli-guide-upgrading#from-202-to-301) to ensure your microservice is now correctly configured.
- Run your microservice from Rider to verify the upgrade worked.

- If you want, re-enable Automatic Code Generation by setting `<GenerateClientCode>true</GenerateClientCode>` in every service's `csproj` file.
  - If you don't want, you can read about manual generation [here](../../../concepts/microservices/#integrating-with-unreal).

**Now, let's go into the Unreal Solution.**

- There were a number of renames and changes, so the project is likely NOT compiling at this point; if most of your work was in Blueprints, those may not be compiling even if the editor is.

- `Target.cs` file and `Beam.Configure___` functions
	- We now add code to your project's `Target.cs` file. This code is callable from any `Target.cs` and `Build.cs` files.
	- Before, you had to manually add the various `BeamableCore` modules to these things by hand. Now, you can call the respective functions based on the Type of `Target` or `Module`.
	- You can refer to the [intro guide](../../intro) to see which functions can be called in which `Target`/`Modules`.

**Initialization** is now manual in all cases.

- Instead of `RegisterOnStarted`/`RegisterOnReady`, you should explicitly invoke: `InitSDK` or `InitSDKWithFrictionlessAuth`.
	- `RegisterOnReady` no longer exists. Its semantics were hard to explain and provided little benefits.
		- It was replaced by `RegisterOnUserReady`.
		- The semantics for this is: "runs at the end of every user's login process, when all the `UBeamRuntimeSubsystems` have already prefetched data for that user".
	  - `RegisterOnStarted` remains the same.
	  - A few delegates have been renamed for clarity:
	    - `FRuntimeStateChangeHandler` => `FBeamRuntimeHandler`
	    - `FUserStateChangedCode`=> `FUserStateChangedHandlerCode`
	  - We removed `IsFirstAuth` and `bDidFirstAuthRun` in favor of a simpler `IsLoggedIn(FUserSlot)` function with which you can build.
	    - The new semantics are slightly different and just tell you that there's a user in that slot or not; you are free to handle "Return to main menu" situation as you wish.
	  - Read more about the initialization flow [here](../../intro).

**Microservice Clients suffered a MAJOR change.**

- Microservices are now generated into their own exclusive Plugin. This makes the Microservice Client code accessible from any other Plugin or Module in your project.
- This means a few things:
	- You must add this plugin to all relevant `Target.cs` and `Build.cs`.
	- You must add this plugin to your Project's `.uproject` file (can be done via the editor, but since you might not be able to compile --- you can do it manually too).
	- If you were using OnlineSubsystemBeamable:
		- Delete the `AutoGen` folder from inside the `Customer` directory.
		- Add the `MicroserviceNameMicroserviceClients` plugin as a dependency to the OnlineSubsystemBeamable plugin.
- If you haven't already, regenerate the microservice clients via by rebuilding them (or running the `dotnet beam generate-client` command).
	- This will create a new Plugin in your project called `MicroserviceNameMicroserviceClients`.
	- This Plugin can be added to any other Plugin or your own project to gain access to the microservice clients and types.
	- About code-changes:
	    - The new clients no longer prefix _every_ generated type with `MicroserviceName`; it only does so for the Request types.
	    - You'll have to go through the code and use the newly generated types.
	    - This change was made to provide you with more control over naming data-types shared between microservice and Unreal and reduce the common-case verbosity of these names.
	    - This means you can fix name conflicts as they appear _in your project_ instead of us preemptively doing it.

