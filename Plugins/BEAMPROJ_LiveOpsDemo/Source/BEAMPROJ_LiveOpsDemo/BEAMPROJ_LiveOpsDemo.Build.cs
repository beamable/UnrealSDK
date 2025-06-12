// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BEAMPROJ_LiveOpsDemo : ModuleRules
{
	public BEAMPROJ_LiveOpsDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		string compactLibInclude = Path.Combine(ModuleDirectory, "ThirdParty", "Compact25519/");
		string blake2bLibInclude = Path.Combine(ModuleDirectory, "ThirdParty", "Blake2b/");
		string libsodiumLibInclude = Path.Combine(ModuleDirectory, "ThirdParty", "libsodium/");

		PublicIncludePaths.AddRange(new string[]
		{
			compactLibInclude,
			blake2bLibInclude
		});


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
		);

		BeamableUnrealMicroserviceClients.AddMicroserviceClients(this);
		Beam.AddRuntimeModuleDependencies(this);
	}
}