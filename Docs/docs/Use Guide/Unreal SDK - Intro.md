<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

# Getting Started
Before you can start using Beamable in your project, sign-up in [our portal](https://portal.beamable.com/login/). 
### Requirements for Beamable
Beamable currently supports **Unreal 5.3.2**.

Beamable also has a dependency on  [.NET Version 8.0](https://dotnet.microsoft.com/en-us/download/dotnet/8.0). This is needed for:

- Installing the Beamable CLI (and therefore enabling the various Beamable workflows).
- Using C# Microservices through the CLI.

Beamable has a hard-dependency on [Docker](https://www.docker.com/products/docker-desktop/). This is needed for two things:

- Building and Deploying Beamable Microservices to your realms (dev/staging/prod environments).
- Running Beamable Microservices without opening the service's project (for non-engineers that want to run microservices locally).

If you don't have these installed, take this opportunity to install them.
## Cloning and Installing Dependencies
Start by getting our repo, then installing .NET and Docker Dekstop.

 1. Clone [UnrealSDK](https://github.com/beamable/UnrealSDK) repo (make sure you have [git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) and [`git-lfs`](https://docs.github.com/en/repositories/working-with-files/managing-large-files/installing-git-large-file-storage) installed).
 2. Checkout the tagged release version from the `main` branch you wish to use (tag format is a semantic version).
 3. Run the `init_repo.sh` script.
	 1. It installs the correct Beamable CLI version globally for you).
	 2. It also sets up this repo so you can look at our [samples](../../Samples/Unreal SDK - Samples Intro).
 4. Optional - [Generate Project Files](https://dev.epicgames.com/documentation/en-us/unreal-engine/how-to-generate-unreal-engine-project-files-for-your-ide?application_version=5.3). 
	 1. On Windows, you can right-click the `.uproject` file and select `Generate Visual Studio project files`.
 5. Optional - Verify things are working by compiling the editor of our SDK project.

Once you have our repo and dependencies set up in your machine, follow along one of the next section to set up the SDK in your project.
### Set up the Beamable SDK - Fast Path
Setting up the SDK in your project is done by manually copying over a set of files from our **Unreal SDK** repo to your project. 

!!! note "Unreal Project Requirements"
	Beamable requires your Unreal project to be a C++ project. That being said, we do provide an entire suite of Blueprint nodes that can be used to achieve *most* of the same functionality.

Please, follow along these instructions:

1. Copy the `beam_init_game_maker.sh` script into the root of your Unreal Project.
2. Copy the `UnrealSDK/Plugins/BeamableCore` plugin into your `Plugins` folder.
3. Add  ```{ "Name": "BeamableCore", "Enabled": true }``` to the array of `Plugins` in your project's `.uproject` file.
4. Open the `UnrealSDK/Source/BeamableUnreal.Target.cs` file and copy the `Beam` class into your `YourGame.Target.cs` file.
	1. Add a `using System;` line to your using statements in `YourGame.Target.cs`.
5. For each existing `Target.cs` file (if one doesn't exist, just don't add it), call the corresponding function in its constructor.
	1. `YourGame.Target.cs` => `Beam.ConfigureGame(this, default);`
	2. `YourGameEditor.Target.cs` => `Beam.ConfigureEditor(this, default);`
	3. `YourGameServer.Target.cs` => `Beam.ConfigureServer(this, default);`
6. For each existing Beamable-dependent Module (if one doesn't exist, just don't add it), add a function call to its `Build.cs` file (see the type of module inside your `uproject` file):
	1. Runtime Modules => `Beam.AddRuntimeModuleDependencies(this);`
	2. UncookedOnly Modules => `Beam.AddUncookedOnlyModuleDependencies(this);`
	3. Editor Modules => `Beam.AddEditorModuleDependencies(this);`
7. Run the `YourProject/beam_init_game_maker.sh` script from inside your project's root directory.
	1. This will install the version of our CLI tool that your SDK version corresponds to locally in your project.
	2. Verify that it worked by running `dotnet beam --version` from inside your project root directory.
8. [Generate Project Files](https://dev.epicgames.com/documentation/en-us/unreal-engine/how-to-generate-unreal-engine-project-files-for-your-ide?application_version=5.3) for your project. 
	 1. On Windows, you can right-click the `YourGame.uproject` file and select `Generate Visual Studio project files`.
9. Open Rider/VS and compile your editor.
#### Making your First Request
Once your Editor opens, you'll see the Beamable Logo in your upper-right bar, next to the Settings dropdown. This button opens the Beamable window.

![BeamableWindowLocation](Images/Unreal_Intro_BeamableWindowLocation.png#center)

In this window, you can login to the account you just created in the Beamable portal. When you do, you should see the window below:

![](Images/Unreal_Intro_BeamableWindowOpened.png#center)

Here's some a quick tour of Beamable terminology:

- `Realm` is an isolated data environment (think of it as a branch, but for your backend). 
	- By default, you have one of these these for your `dev`, `staging` and `prod` environments.
	- The `ApplyToBuild` button sets the realm information in the `Config/DefaultEngine.ini` file of your project. Whatever realm is configured in this file, is the realm your build will be pointed towards. [Dedicated Server Builds](../Unreal SDK - Dedicated Servers) don't need to care about their baked in `TargetRealm`. They fetch their target realm from Environment Variables.
- `Content` opens up the **Content Window**.  See the [Content Docs](../../Feature Guides/Unreal SDK - Content) for more info.
- `Open Portal` opens the **Portal** in your default web-browser already logged in with your editor user and pointed at your current realm.
- `Microservices` opens the **Microservice Window**. See the [Microservice Docs](../../Feature Guides/Unreal SDK - Microservices) for more info.
- `Reset PIE Users` (Play-In-Editor) removes your PIE users locally cached data. 
	- By default, when you sign into a Beamable account in PIE (in your game code), Beamable will use the same user until you delete the files `Saved/Beamable/UserSlots/PIE_XXXXX.json`. This button does that for you. After you click it, the next time you enter PIE, a brand new Beamable player account will be created in your current realm.

Now that you are familiar with the **Beamable Window**, you are ready to make your first Beamable request (we'll do it via Blueprint, but you can do the exact same flow in C++ by making these calls in your Project's `GameMode` class's `BeginPlay` function).

To get started, open your Level Blueprint and add the following pattern:

![](Unreal_Intro_OnBeamableReady.png#center)

The `BeamRuntime` is an `GameInstanceSubsystem` that is responsible for controlling the SDK's lifecycle and, in clients, player authentication. 

!!! warning "Runtime Concepts Guide"
	The [Runtime Concepts Guide](../Unreal SDK - Runtime Concepts) explains how the Beamable Runtime works. Please read it after you are done with this guide as the default Beamable configuration might not be the best fit for your type of game and it'll give you examples of common setups.

Now that you have this event hooked up, you can add your first **Beam Flow Node**. These nodes are custom nodes that wrap around the following functionality:

- Creating a new Request `UObject`.
- Getting a `UBeam___Api` engine subsystem. 
	- This is a stateless system that exposes an auto-generated API to talk to various services.
	- This is not the recommended way you'll use Beamable. Its just the simplest way for you to get started.
- A set of Custom Event nodes (for success, error and completion) of the request being made to the Beamable backe-end.
	- Because of this, Unreal does not allow the use of these nodes (or any node that expands to Event nodes) outside of **EventGraphs** or **Macros used in EventGraphs**.

![Unreal_Intro_BeamFlowNode.png](Images/Unreal_Intro_BeamFlowNode.png#center)

With the SDKs default configuration and the above setup, you can enter PIE (Play-In-Editor). You should see several requests's responses being written to your Output Log window. After you see the final `GetMe` request, you can exit PIE knowing you've very first request to the Beamable backend.

#### Additional Information
Before we complete this guide, there's one final thing that is important to know. You can, and should, use verbose logging `log "Category" Verbose` when you encounter an issue stemming from our SDK (Log Categories can be found in `BeambleCore/BeamLogging.h` file). 

This verbose logging will print out ***everything*** about the request being made. Its meant to aid us in diagnosing issues that you may encounter when using the SDK AND not for production use. To turn it off in the same editor session, just run `log LogBeamBackend Display` in the editor console.

When reporting an issue, try to reproduce the issue with the logs of the relevant systems set to Verbose and attach them to the issue.
#### Next Steps
Now that you've made your first Beamable Request, take a look at the [Unreal SDK - Runtime Concepts](../Unreal SDK - Runtime Concepts) page so you understand more about how the SDK is structured and the various paths to using it and the best path for your game.

If you'd like to see a more complicated example running on Beamable, take a look at [our Samples](../../Samples/Unreal SDK - Samples Intro).
