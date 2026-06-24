using System.IO;
using UnrealBuildTool;

public class BeamPlatformNotifications : ModuleRules
{
    public BeamPlatformNotifications(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "Json"
        });

        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            // Link the prebuilt Swift core. UE expects a DYNAMIC .framework zipped as
            // <Name>.embeddedframework/<Name>.framework, staged into ThirdParty/ by setup-unreal.sh.
            // bCopyFramework MUST be true: the framework's install name is @rpath/..., so it has
            // to be embedded into the app bundle's Frameworks/ (otherwise dyld fails at launch with
            // "Library not loaded: @rpath/BeamableNotifications.framework/BeamableNotifications").
            // FrameworkMode.LinkAndCopy = link + embed into the app bundle's Frameworks/ (same
            // pattern OnlineSubsystemGoogle uses for its dynamic frameworks).
            PublicAdditionalFrameworks.Add(new Framework(
                "BeamableNotifications",
                Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "BeamableNotifications.embeddedframework.zip"),
                Framework.FrameworkMode.LinkAndCopy
            ));

            // UPL injects entitlements (push, App Group), background modes, the URL scheme,
            // and stages the Notification Service Extension into the generated Xcode project.
            AdditionalPropertiesForReceipt.Add("IOSPlugin",
                Path.Combine(ModuleDirectory, "IOS", "BeamPlatformNotifications_UPL.xml"));

            PublicFrameworks.AddRange(new string[] { "UserNotifications" });
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            // The Kotlin core (beamable-notifications-release.aar) is imported and its
            // gradle/Firebase deps + manifest entries + onNewIntent hook are injected by the APL.
            // JNI helpers (AndroidJavaEnv / FJavaHelper) live in Core, already a public dep.
            AdditionalPropertiesForReceipt.Add("AndroidPlugin",
                Path.Combine(ModuleDirectory, "Android", "BeamPlatformNotifications_APL.xml"));
        }
    }
}
