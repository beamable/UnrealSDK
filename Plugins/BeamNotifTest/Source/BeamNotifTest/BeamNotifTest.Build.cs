using UnrealBuildTool;

public class BeamNotifTest : ModuleRules
{
    public BeamNotifTest(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "Json",
            "BeamableCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate", "SlateCore", "UMG",
            "BeamableCoreRuntime",
            "BeamableUnrealMicroserviceClients",
            "BeamPlatformNotifications"
        });
    }
}
