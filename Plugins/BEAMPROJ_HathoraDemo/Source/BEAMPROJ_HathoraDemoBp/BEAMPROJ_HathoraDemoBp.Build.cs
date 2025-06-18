using UnrealBuildTool;

public class BEAMPROJ_HathoraDemoBp : ModuleRules
{
    public BEAMPROJ_HathoraDemoBp(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Engine",
                "CoreUObject",
                "BeamableCore",
                "BeamableCoreBlueprintNodes",
                "BEAMPROJ_HathoraDemo",
                
                "UnrealEd",
                "BlueprintGraph",
                "Kismet",
                "KismetCompiler",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
    }
}