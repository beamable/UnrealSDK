using UnrealBuildTool;

public class BEAMPROJ_BeamballBlueprintNodes : ModuleRules
{
    public BEAMPROJ_BeamballBlueprintNodes(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "BEAMPROJ_Beamball",

                "BeamableCore",
                "BeamableCoreRuntime",
                "BeamableCoreBlueprintNodes",
                

                "BlueprintGraph",
                "UnrealEd"
            });


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",					
            });
    }
}