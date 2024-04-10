using UnrealBuildTool;
using System.Collections.Generic;

public class BeamableUnrealServerTarget : TargetRules
{
    public BeamableUnrealServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        bUsesSteam = false; // Set to true if using Steam

        // Only include the core and necessary modules for the server build
        ExtraModuleNames.AddRange(new string[]
        {
            "BeamableUnreal", 
            
            "BeamableCore",
            "BeamableCoreRuntime",
            
            // Server specific modules can be added here
            "OnlineSubsystem", // If using any online subsystem
            "OnlineSubsystemUtils",
        });
    }
}
