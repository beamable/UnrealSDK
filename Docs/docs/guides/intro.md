<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

# Getting Started
Before you can start using Beamable in your project, sign-up in [our portal](https://portal.beamable.com/login/). 
## Cloning and Installing Dependencies
Start by getting our repo, then installing .NET and Docker Dekstop.

 1. Clone [UnrealSDK](https://github.com/beamable/UnrealSDK) repo (make sure you have `git-lfs` installed).
 2. Check out the a [tagged release version](https://github.com/beamable/UnrealSDK/releases) (in the form `X.X.X`).
 3. Run the `init_repo.sh` script (on Windows, use GitBash or any other shell).
 4. Generating Project Files.
 5. Optional - Verify things are working by compiling the editor of our SDK project.

Next up, install our dependencies.

 - [Docker Desktop](https://www.docker.com/products/docker-desktop/)
 - [.NET](https://dotnet.microsoft.com/en-us/download/dotnet/8.0)

Once you have our repo and dependencies set up in your machine, follow along one of the next section to set up the SDK in your project.
### Set up the Beamable SDK - Fast Path
Setting up the SDK in your project is done by manually copying over a set of files from our **Unreal SDK** repo to your project. 

!!! note "Unreal Project Requirements"
	Beamable requires your Unreal project to be a C++ project. That being said, we do provide an entire suite of Blueprint nodes that can be used to achieve *most* of the same functionality.

Please, follow along these instructions:

1. Copy the `beam_init_game_maker.sh` script into the root of your Unreal Project.
2. From a terminal running in your project directory, run the copied script passing in the path to the **UnrealSDK** in your machine.
	1. `. beam_init_game_maker.sh "E:/Path/To/UnrealSDK"`
	2. `. beam_init_game_maker.sh "E:/Path/To/UnrealSDK" true`, if you're planning to use the `OnlineSubsystemBeamable`.
3. For each of your `Target.cs` files, add the following lines to their constructor:
	1. `MyProject.Target.cs => Beam.ConfigureGame(this, Beam.OssConfig.Disabled())`.
	2. `MyProjectEditor.Target.cs => Beam.ConfigureEditor(this, Beam.OssConfig.Disabled())`.
	3. `MyProjectServer.Target.cs => Beam.ConfigureServer(this, Beam.OssConfig.Disabled())`, if you have dedicated server builds.
4. In each of the Modules you want to use Beamable's SDK, add this to their `Build.cs` files:
	1. `RuntimeModule.Build.cs => Beam.AddRuntimeModuleDependencies(this);`
	2. `EditorModule.Build.cs => Beam.AddEditorModuleDependencies(this);`
	3. `UncookedOnlyModule.Build.cs => Beam.AddUncookedOnlyModuleDependencies(this);`
	4. Pay attention to the type of module you're adding the SDK to and call the proper function. (You can see the module type in your `uproject` file)
5. Some OS-specific things:
	1. On MacOS, you'll have to manually regenerate project files. 
	2. On Windows, this was done by `beam_init_game_maker.sh` script.
6. Verify that your project is set up correctly:
	1. Check there is a `.beamable` folder in your project root directory.
	2. Check there is a `.config/dotnet-tools.json` file in your project directory.
	3. Run `dotnet beam --version` from inside your project root directory and see that it outputs a valid `X.Y.Z` string.
7. Open Rider/VS and compile your editor.
#### Making your First Request
Once your Editor opens, you'll see the Beamable Logo in your upper-right bar, next to the Settings dropdown. This button opens the Beamable window.

![BeamableWindowLocation](Images/intro-beamable-window-location.png#center)

In this window, you can login to the account you just created in the Beamable portal. When you do, you should see the window below:

![](Images/intro-beamable-window-opened.png#center)

Here's some a quick tour of Beamable terminology:

- `Realm` is an isolated data environment (think of it as a branch, but for your backend). 
	- By default, you have one of these these for your `dev`, `staging` and `prod` environments.
	- The `ApplyToBuild` button sets the realm information in the `Config/DefaultEngine.ini` file of your project. Whatever realm is configured in this file, is the realm your build will be pointed towards. [Dedicated Server Builds](../guides/dedicated-servers.md) don't need to care about their baked in `TargetRealm`. They fetch their target realm from Environment Variables.
- `Content` opens up the **Content Window**.  See the [Content Docs](../features/content.md) for more info.
- `Open Portal` opens the **Portal** in your default web-browser already logged in with your editor user and pointed at your current realm.
- `Microservices` opens the **Microservice Window**. See the [Microservice Docs](../features/microservices.md) for more info.
- `Reset PIE Users` (Play-In-Editor) removes your PIE users locally cached data. 
	- By default, when you sign into a Beamable account in PIE (in your game code), Beamable will use the same user until you delete the files `Saved/Beamable/UserSlots/PIE_XXXXX.json`. This button does that for you. After you click it, the next time you enter PIE, a brand new Beamable player account will be created in your current realm.

Now that you are familiar with the **Beamable Window**, you are ready to make your first Beamable request (we'll do it via Blueprint, but you can do the exact same flow in C++ by making these calls in your Project's `GameMode` class's `BeginPlay` function).

To get started, open your Level Blueprint and add the following pattern:

![](images/intro-on-beamable-ready.png#center)

The `BeamRuntime` is an `GameInstanceSubsystem` that is responsible for controlling the SDK's lifecycle and, in clients, player authentication. 

!!! warning "Runtime Concepts Guide"
	The [Runtime Concepts Guide](runtime-concepts.md) explains how the Beamable Runtime works. Please read it after you are done with this guide as the default Beamable configuration might not be the best fit for your type of game and it'll give you examples of common setups.

Now that you have this event hooked up, you can add your first **Beam Flow Node**. These nodes are custom nodes that wrap around the following functionality:

- Creating a new Request `UObject`.
- Getting a `UBeam___Api` engine subsystem. 
	- This is a stateless system that exposes an auto-generated API to talk to various services.
	- This is not the recommended way you'll use Beamable. Its just the simplest way for you to get started.
- A set of Custom Event nodes (for success, error and completion) of the request being made to the Beamable backe-end.
	- Because of this, Unreal does not allow the use of these nodes (or any node that expands to Event nodes) outside of **EventGraphs** or **Macros used in EventGraphs**.

![intro-beam-flow-node.png](images/intro-beam-flow-node.png#center)

With the SDKs default configuration and the above setup, you can enter PIE (Play-In-Editor). You should see several requests's responses being written to your Output Log window. After you see the final `GetMe` request, you can exit PIE knowing you've very first request to the Beamable backend.

#### Additional Information
Before we complete this guide, there's one final thing that is important to know. You can, and should, use verbose logging `log "Category" Verbose` when you encounter an issue stemming from our SDK (Log Categories can be found in `BeambleCore/BeamLogging.h` file). 

This verbose logging will print out ***everything*** about the request being made. Its meant to aid us in diagnosing issues that you may encounter when using the SDK AND not for production use. To turn it off in the same editor session, just run `log LogBeamBackend Display` in the editor console.

When reporting an issue, try to reproduce the issue with the logs of the relevant systems set to Verbose and attach them to the issue.
#### Next Steps
Now that you've made your first Beamable Request, take a look at the [Runtime Concepts](runtime-concepts.md) page so you understand more about how the SDK is structured and the various paths to using it and the best path for your game.

If you'd like to see a more complicated example running on Beamable, take a look at [our Samples](../samples/intro.md).
