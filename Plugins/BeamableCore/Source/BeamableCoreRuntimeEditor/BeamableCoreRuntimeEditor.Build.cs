using UnrealBuildTool;

public class BeamableCoreRuntimeEditor : ModuleRules
{
    public BeamableCoreRuntimeEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

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
                "SlateCore"
            }
        );
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "BeamableCore",
                
                "Core",
                "Engine",
                "CoreUObject",
                "UnrealEd",
                "SlateCore",
                "Slate",
                "EditorStyle",
                "Kismet",
                "KismetCompiler",
                "Projects", // Required to use IPluginManager in order to configure new Slate styles
                "ToolMenus",
                "ToolMenusEditor",
                "UMGEditor",
                "DeveloperSettings",
                "EditorSubsystem",
                "Json",
                "JsonUtilities",
                "DataTableEditor",
                "DeveloperToolSettings",
                "AssetTools"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "BlueprintGraph",
                "GraphEditor",
                "LevelEditor",
                "PropertyEditor",
                "UMGEditor",
                "Blutility",
                "DeveloperToolSettings",
                "UnrealEd",
                "ToolWidgets",
                "EditorScriptingUtilities",
                "HTTP",
            }
        );
    }
}