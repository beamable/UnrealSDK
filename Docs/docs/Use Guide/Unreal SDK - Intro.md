<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
## Getting Started
### Signing Up and Realm Configuration

Before you can start using Beamable in your project, sign-up in [our portal](https://portal.beamable.com/login/). Once that is done, configure each of your realms to use the notification pipeline the Unreal SDK supports. To do that, go into each of your realms in the portal and apply the following realm config:

> **Namespace:** `notification`
> **Key**: `publisher`
> **Value**: `beamable`

![Portal Realm Config](Images/Unreal_Intro_RealmConfiguration.png#center)

Now that you have an Organization and Game created with Beamable, you can add the Beamable SDK plugin to your project.
### Setting up the Beamable SDK in your Project

Download the correct tagged Release file from our [SDK's GitHub](https://github.com/beamable/UnrealSDK/releases). The release zipped file can be unzipped directly into your project's root. This will make sure you have all the files you need in the Plugins folder; it'll also extract a few utility scripts into the `.beamable/local_tools/`directory as well as `installOrUpdate.sh/bat` scripts. 

Now that everything is extracted, let's make some changes to your `Target.cs` files.

```cs
// Add to YourGameGame.Target.cs
ExtraModuleNames.AddRange(new string[] { "BeamableCore", "BeamableCoreRuntime", "BeamableCoreBlueprintNodes" });

// If you have an Editor Module, add this to YourGameEditor.Target.cs
ExtraModuleNames.AddRange(new string[] { "BeamableCore", "BeamableCoreEditor", "BeamableCoreBlueprintNodes" });

// If you're game has a dedicated server build, add this to YourGameServer.Target.cs
ExtraModuleNames.AddRange(new string[] { "BeamableCore", "BeamableCoreRuntime", });

// If you're game has a client-only build, add this to YourGameClient.Target.cs
ExtraModuleNames.AddRange(new string[] { "BeamableCore", "BeamableCoreRuntime", });
```

You'll also need to add the appropriate modules to your `Build.cs` files of modules that want to access the SDK itself.

```cs
// Add to YourGame.Build.cs
PublicDependencyModuleNames.AddRange(
	new string[] {
		// ... Other Modules ...
		"BeamableCore",
		"BeamableCoreRuntime",
	}
);

// Add to YourGameEditor.Build.cs
 PrivateDependencyModuleNames.AddRange(
	new string[] {
		// ... Other modules ...
		"BeamableCore",
		"BeamableCoreEditor",
		"BeamableCoreBlueprintNodes",
	}
);
```

After updating these files, you should run the `installOrUpdate.sh/bat` for your OS. This script will:

- Download and extract the correct [Beamable CLI](../../#beamable-cli) into the `.beamable/local_tools` directory.
- It'll add the `.beamable/local_tools` directory to your PATH 
	- If you are working with multiple Beamable projects, you'll have the option to add a suffix to the installed CLI name to avoid conflicts (default is `beam` but you can have it be `beam-proj-A`).
- It'll run the Generate Project Files process for you.

Once this file is done, compile and run the `Development | Editor` target for your project from your IDE and you're ready to make your first Beamable request.
### The Beamable Window

Once your Editor opens, you'll see the Beamable Logo in your upper-right bar, next to the Settings dropdown. This button opens the Beamable window.

![BeamableWindowLocation](Images/Unreal_Intro_BeamableWindowLocation.png#center)

In this window, you can login to the account you just created in the Beamable portal. When you do, you should see the window below:

![](Images/Unreal_Intro_BeamableWindowOpened.png#center)

Here's some a quick tour of Beamable terminology:

- `Realm` shows which realm you are in.
	- The `ApplyToBuild` button sets the realm information in the `Config/DefaultEngine.ini` file of your project. Whatever realm is configured in this file, is the realm your build will be pointed towards.
	- ***When you get started, don't forget to use the dropdown to change over to your game's dev realm. At the moment, the first sign in points you at your production realm instead.***
	- [Dedicated Server Builds](../Use Guide/Unreal SDK - Dedicated Servers) don't need to care about their baked in `TargetRealm`. They fetch their target realm from Environment Variables.
- `Content Manifests`, is always  `global`. At the moment we don't support multiple manifests in UE. See the [Content Docs](../Unreal SDK - Content) for more info on how to use our content system.
- `Open Portal` opens the **Beamable Portal** in your default web-browser already logged in with your editor user and pointed at your current realm.
- `Microservices` opens the **Beamable Microservice Window**. See the [Microservice Docs](../Unreal SDK - Microservices) for more info on how to get started with microservices.
- `Reset PIE Users` (Play-In-Editor) removes your PIE users locally cached data. 
	- By default, when you sign into a Beamable account in PIE (in your game code), Beamable will use the same user until you delete the files `Saved/Beamable/UserSlots/PIE_XXXXX.json`. This button does that for you. After you click it, the next time you enter PIE, a brand new Beamable player account will be created.

### Making your First Request

Now that you are familiar with the **Beamable Window**, you are ready to make your first Beamable request (we'll do it via Blueprint, but you can do the exact same flow in C++ by making these calls in your Project's `GameMode` class's `BeginPlay` function).

To get started, open your Level Blueprint and add the following pattern:

![](Unreal_Intro_OnBeamableReady.png#center)

The `BeamRuntime` is an `EngineSubsystem` that is responsible for controlling the SDK's lifecycle and, in clients, player authentication. 

The [Runtime Concepts Guide](../Unreal SDK - Runtime Concepts) explains how the Beamable Runtime works. Please read it after you are done with this guide as the default Beamable configuration might not be the best fit for your type of game and it'll give you examples of common setups.

Now that you have this event hooked up, you can add your first **Beam Flow Node**. These nodes are custom nodes that wrap around the following functionality:

- Creating a new Request `UObject`.
- Getting a `UBeam___Api` engine subsystem. 
	- This is a stateless system that exposes an auto-generated API to talk to various services.
	- This is not the recommended way you'll use Beamable. Its just the simplest way for you to get started.
- A set of Custom Event nodes (for success, error and completion) of the request being made to the Beamable backe-end.
	- Because of this, Unreal does not allow the use of these nodes (or any node that expands to Event nodes) outside of **EventGraphs** or **Macros used in EventGraphs**.

![Unreal_Intro_BeamFlowNode.png](Images/Unreal_Intro_BeamFlowNode.png#center)

With the SDKs default configuration and the above setup, you can enter PIE (Play-In-Editor). You should see several requests's responses being written to your Output Log window. After you see the final `GetMe` request, you can exit PIE.

### Additional Information
Before we complete this guide, there's one final thing that is important to know. You can, and should, use verbose logging `log "Category" Verbose`  (Log Categories can be found in `BeambleCore/BeamLogging.h` file). Keep in mind that this verbose logging will print out ***everything*** about the request being made and response coming in. Its meant to aid us in diagnosing issues that you may encounter when using the SDK AND not for production use. To turn it off in the same editor session, just run `log LogBeamBackend Display` in the editor console.

When reporting an issue, try to reproduce the issue with the logs of the relevant systems set to Verbose and attach them to the issue.

### Next Steps
Now that you've made your first Beamable Request, take a look at the [[Unreal SDK - Runtime Concepts]] page so you understand more about how the SDK is structured and the various paths to using it and the best path for your game.