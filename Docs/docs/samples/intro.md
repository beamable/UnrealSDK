# Setting Up The Sample Projects

Beamable provides sample projects for Unreal as part of the Unreal SDK repository. Each sample is tied to a plugin named `BEAMPROJ_<PluginName>` of a shared `BeamableUnreal` project. The sample you see in the editor is determined by which `BEAMPROJ_` plugin is enabled in the BeamableUnreal.uproject file.

## Preparing the Environment
1. Install Dependencies
      - NET 8.0
      - [Docker Desktop](https://www.docker.com/products/docker-desktop/)
2. Clone the UnrealSDK Repository
      - Clone the [UnrealSDK](https://github.com/Beamable/UnrealSDK) repository if you didn't yet.
      - Run the `prepare_repo.sh` Script. (We recommend using GitBash, but any similar shell should work)

## Select the Sample to Run

1. Use `dotnet beam unreal select-sample BEAMPROJ_<PluginName>` to switch to the plugin (and thus the sample) you want. During this process all of the content in their `Override` folder will be copied to the `BeamamableUnreal` project replacing any previous configuration. This allow us to replace the whole "Context" in which the project will be configured, thus allowing us to have multiple samples at the same project.
2. For example, `dotnet beam unreal select-sample BEAMPROJ_HathoraDemo` switches the repo to the Hathora Demo sample
3. If using Rider as IDE and already in the BeamableUnreal.sln project you can alternatively select and run the `SET BEAMPROJ - <PluginName>` in the Configuration Drop Down (Top Right Corner)

## Build and Run in Editor

1. Open the generated `.sln` file in your IDE (e.g., Visual Studio, Rider...).
2. Perform a Clean build of the Editor target.
3. Run the `BeamableUnreal` Project and in the editor, go to Project Settings → Beamable Core → Beamable Environment and verify it’s set to `BeamProdEnv`.
4. Sign in to your Beamable account in the Beamable Window.
5. Follow Sample-Specific Instructions. Each sample has its own documentation for additional steps or guidance.

!!! warning "Clean Up Sample Realms"
      If you are using your own organization (the one you’ll use to ship your game) to test any of these samples, don’t forget to delete the test realms when you’re finished exploring!


## Why Using a Single Repository?
We keep all Beamable samples within the main repository so we can:

- Use as QA Tools: We continuously develop and test against our own samples.
- Ensure Up-to-Date Samples: Whenever we update the SDK, the sample projects are updated too. Maintaining samples alongside core features makes it easier to keep everything stable and consistent.

To make this work as should we keep the `Config` and `.beamable` folders in sync. This is done by:

- Our custom `Target.cs` code that will make the `Config` and `.beamable` folders at the root level of the repo be exact copies of the folders inside the `Overrides` directory of each `BEAMPROJ_` folder. In other words, the contents of those folders at the root level is defined by the selected `BEAMPROJ`.
- An editor subsystem called `BeamProjSync` that, while the editor is running, file-watches those directories and copies changes made over to the appropriate `BEAMPROJ_` `Overrides` folder.
- Those implementations are only related to the especificity of this sample configuration and it's not related to the samples content themselves.