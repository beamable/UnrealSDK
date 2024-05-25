Unreal Beamable Samples are distributed as a configuration of the Unreal SDK repository. We call these `BeamProj`. The `BeamProjOverride.txt` file at the root of the Unreal SDK project defines which of the `BEAMPROJ_` plugins is the active sample.

To look at any given sample, you need to:

1. Change the contents of the `BeamProjOverride.txt` file to match the `BEAMPROJ_Plugin` of your choice. For example, `BEAMPROJ_HathoraDemo` would configure the repository as the Hathora Demo sample.
2. Generate Project Files.
3. Open the solution and do a clean build.

Instructions for seeing each sample can be found in their respective sample docs.

!!! note "Why not a separate repository?"
	Workflow is important to us. We want to maintain these sample projects over the long run as a means to dogfood our own tools. So... our samples are part of our repo to minimize developer friction which translates to up-to-date samples and better stability for our product.

