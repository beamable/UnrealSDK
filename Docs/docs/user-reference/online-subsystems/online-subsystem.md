# Unreal Online Subsystems

To use our Online Subsystem integration to Unreal Online Subsystems, you'll need to update your `*.Target.cs` 's `Beam.ConfigureGame` method call. As well as re-running, `beam-init-game-maker.sh "Path/To/SDK/Clone" true` with a second argument as true.

To enable the Enabling Online Subsystem would require updating the value of the second argument of that method, `Beam.OssConfig` value, example values for Hathora sample project:

```csharp
var oss = new Beam.OssConfig()
{
    IsEnabled = true,

    HooksEnabled = true,
    HookSubsystemImplementation = "FOnlineSubsystemHathoraDemo",
    HookSubsystemIncludePath = "Customer/OnlineSubsystemHathoraDemo.h",

    AdditionalHookModules = new[] { "HathoraSDK" }
};
```
