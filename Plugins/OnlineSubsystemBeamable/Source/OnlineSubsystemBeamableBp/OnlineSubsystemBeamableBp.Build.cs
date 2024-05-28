using UnrealBuildTool;

public class OnlineSubsystemBeamableBp : ModuleRules
{
    public OnlineSubsystemBeamableBp(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "BeamableCore",
                "BeamableCoreRuntime",
                "BeamableCoreBlueprintNodes",
                "OnlineSubsystemBeamable",
                "BlueprintGraph",
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