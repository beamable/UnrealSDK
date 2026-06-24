using UnrealBuildTool;

public class BeamNotifTestEditor : ModuleRules
{
    public BeamNotifTestEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate", "SlateCore", "UnrealEd", "ToolMenus", "Projects", "InputCore", "Json"
        });
    }
}
