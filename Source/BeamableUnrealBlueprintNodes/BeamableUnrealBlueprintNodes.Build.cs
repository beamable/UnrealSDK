using UnrealBuildTool;

public class BeamableUnrealBlueprintNodes : ModuleRules
{
    public BeamableUnrealBlueprintNodes(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        Beam.AddUncookedOnlyModuleDependencies(this, true);
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                
                "BeamableUnreal",
                "BlueprintGraph"
            }
        );
    }
}