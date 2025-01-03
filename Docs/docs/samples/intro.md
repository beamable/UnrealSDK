<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

Unreal Beamable Samples are distributed as a configuration of the Unreal SDK repository. We call these `BeamProj`. The selected `BeamProj` is defined by which of the `BEAMPROJ_` plugins is the enabled one inside the `BeamableUnreal.uproject` file.

To look at any given sample, you need to:

1. Have our dependencies installed ( [.NET](https://dotnet.microsoft.com/en-us/download/dotnet/8.0) and [Docker](https://www.docker.com/products/docker-desktop/))
2. Clone our [UnrealSDK](https://github.com/beamable/UnrealSDK) repository.
3. Run the `prepare_repo.sh` script (we run it through GitBash but any similar shell *should* work).
4. Run `dotnet beam unreal select-sample BEAMPROJ_Plugin` to match the `BEAMPROJ_Plugin` of your choice. 
	1. For example, `BEAMPROJ_HathoraDemo` sets the repository as the Hathora Demo sample.
	2. You can find the correct `BEAMPROJ_` at the each sample's page.
5. Open the project's `.sln` and do a clean build of the `Editor` target.
6. Open the editor and `Project Settings -> Beamable Core -> Beamable Environment` and verify that it is set to `BeamProdEnv` before signing into a Beamable account.

Further instructions for seeing each sample can be found in their respective sample docs.

!!! note "Why not a separate repository?"
	Workflow is important to us. We want to maintain these sample projects over the long run as a means to dogfood our own tools. So... our samples are part of our repo to minimize developer friction which translates to up-to-date samples and better stability for our product; which hopefully translates for a better product for the people making amazing games with it.

!!! warning "Clean Up"
	If you are using your own organization (the one you'll use to ship your game) to test these samples out, don't forget to delete the realms once you're done exploring the samples!

#### More Information (Irrelevant for non-Beamable Devs)
To make each plugin function as its own little UE project. We have to keep the `Config` and `.beamable` folders in sync. This is done by:

- Our custom `Target.cs` code that will make the `Config` and `.beamable` folders at the root level of the repo be exact copies of the folders inside the `Overrides` directory of each `BEAMPROJ_` folder.
	- In other words, the contents of those folders at the root level is defined by the selected `BEAMPROJ`.
- An editor subsystem called `BeamProjSync` that, while the editor is running, file-watches those directories and copies changes made over to the appropriate `BEAMPROJ_` `Overrides` folder.