#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Textures/SlateIcon.h"

/// One connected iOS device, as reported by `xcrun devicectl list devices`.
struct FBeamNotifDevice
{
    FString Udid;
    FString Name;
    FString State;     // e.g. "connected" / "disconnected"
    FString Label() const { return FString::Printf(TEXT("%s  [%s]"), *Name, *State); }
};

/// Editor-only module: adds an "iOS + NSE → Device" button to the Level Editor toolbar.
/// On click it lists connected devices, lets you pick one in-editor, then runs
/// package-ios-deploy.sh as a CHILD PROCESS, streaming its output to the Output Log
/// (LogBeamNotif). While running, the button turns into a "Cancel" button.
class FBeamPlatformNotificationsEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void RegisterMenus();

    // Toolbar button (state-dependent: start vs cancel).
    void OnToolbarButtonClicked();
    FText GetButtonLabel() const;
    FText GetButtonTooltip() const;
    FSlateIcon GetButtonIcon() const;

    void StartPipelineFlow();
    void CancelPipeline();

    static void MakeScriptsExecutable();
    static bool QueryDevices(TArray<TSharedPtr<FBeamNotifDevice>>& OutDevices);
    static bool ShowDevicePicker(const TArray<TSharedPtr<FBeamNotifDevice>>& Devices, FString& OutUdid);

    /// Run package-ios-deploy.sh as a child process, streaming output to LogBeamNotif.
    void LaunchPipeline(const FString& Udid);

    TSharedPtr<class FMonitoredProcess> DeployProcess;
    bool bDeployRunning = false;   // game-thread view of whether a run is active
    bool bPipelineOk = false;      // set on the process thread when the success marker is seen
};
