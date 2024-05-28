<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

Unreal Beamable Samples are distributed as a configuration of the Unreal SDK repository. We call these `BeamProj`. The `BeamProjOverride.txt` file at the root of the Unreal SDK project defines which of the `BEAMPROJ_` plugins is the active sample.

To look at any given sample, you need to:

1. Have our dependencies installed ( [.NET](https://dotnet.microsoft.com/en-us/download/dotnet/6.0) and [Docker](https://www.docker.com/products/docker-desktop/))
2. Clone our [UnrealSDK](https://github.com/beamable/UnrealSDK) repository and run the `init_repo.sh` script (we run it through GitBash but any shell should work).
3. Change the contents of the `BeamProjOverride.txt` file to match the `BEAMPROJ_Plugin` of your choice. 
	1. For example, `BEAMPROJ_HathoraDemo` sets the repository as the Hathora Demo sample.
4. Generate Project Files.
5. Open the solution and do a clean build of the editor.
6. Open the editor and `Project Settings -> Beamable Core -> Beamable Environment` and set it to `BeamProdEnv` before signing into a Beamable account.

Further instructions for seeing each sample can be found in their respective sample docs.

!!! note "Why not a separate repository?"
	Workflow is important to us. We want to maintain these sample projects over the long run as a means to dogfood our own tools. So... our samples are part of our repo to minimize developer friction which translates to up-to-date samples and better stability for our product.

