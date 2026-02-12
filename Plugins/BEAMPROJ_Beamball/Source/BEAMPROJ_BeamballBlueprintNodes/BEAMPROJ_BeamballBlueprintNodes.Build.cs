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
                "Engine",
                "CoreUObject",
                "BeamableCore",
                "BeamableCoreRuntime",
                "UnrealEd",
                "BlueprintGraph",
                "GraphEditor",
                "PropertyEditor",
                "SlateCore",
                "Slate",
                "EditorStyle",
                "Kismet",
                "KismetCompiler",
                "Projects", // Required to use IPluginManager in order to configure new Slate styles
                "ToolMenus",
                "ToolMenusEditor", 
                "DeveloperSettings",
                "BeamableCoreRuntime", 
                "BeamableCoreBlueprintNodes"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
            }
        );
    }
}