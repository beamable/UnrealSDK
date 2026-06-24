#include "BeamPlatformNotificationsEditorModule.h"

#include "ToolMenus.h"
#include "Framework/Commands/UIAction.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "HAL/PlatformProcess.h"
#include "HAL/FileManager.h"
#include "Misc/MonitoredProcess.h"
#include "Misc/Attribute.h"
#include "Async/Async.h"
#include "Styling/AppStyle.h"
#include "Interfaces/IPluginManager.h"

// Absolute path to this plugin's bundled Scripts/ directory (where add-nse.sh +
// package-ios-deploy.sh live). The plugin is self-contained, so the scripts travel with it.
static FString BMN_ScriptsDir()
{
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("BeamPlatformNotifications"));
    const FString Base = Plugin.IsValid()
        ? Plugin->GetBaseDir()
        : (FPaths::ProjectPluginsDir() / TEXT("BeamPlatformNotifications"));
    return FPaths::ConvertRelativePathToFull(Base / TEXT("Scripts"));
}

#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "Framework/Application/SlateApplication.h"
#include "Widgets/SWindow.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboBox.h"

#define LOCTEXT_NAMESPACE "BeamPlatformNotificationsEditor"

DEFINE_LOG_CATEGORY_STATIC(LogBeamNotif, Log, All);

void FBeamPlatformNotificationsEditorModule::StartupModule()
{
    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBeamPlatformNotificationsEditorModule::RegisterMenus));
}

void FBeamPlatformNotificationsEditorModule::ShutdownModule()
{
    if (DeployProcess.IsValid())
    {
        DeployProcess->Cancel(true);
    }
    DeployProcess.Reset();

    UToolMenus::UnRegisterStartupCallback(this);
    UToolMenus::UnregisterOwner(this);
}

void FBeamPlatformNotificationsEditorModule::RegisterMenus()
{
    FToolMenuOwnerScoped OwnerScoped(this);

    if (UToolMenu* Toolbar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar"))
    {
        FToolMenuSection& Section = Toolbar->FindOrAddSection("BeamNotifTest");
        // Label / tooltip / icon are dynamic (TAttribute), so the button flips to "Cancel"
        // while a run is active — Slate re-evaluates these each frame.
        FToolMenuEntry Entry = FToolMenuEntry::InitToolBarButton(
            "PackageIOSWithNSE",
            FUIAction(FExecuteAction::CreateRaw(this, &FBeamPlatformNotificationsEditorModule::OnToolbarButtonClicked)),
            MakeAttributeLambda([this]() { return GetButtonLabel(); }),
            MakeAttributeLambda([this]() { return GetButtonTooltip(); }),
            MakeAttributeLambda([this]() { return GetButtonIcon(); }));
        Section.AddEntry(Entry);
    }
}

FText FBeamPlatformNotificationsEditorModule::GetButtonLabel() const
{
    return bDeployRunning ? LOCTEXT("CancelLabel", "Cancel iOS Deploy")
                          : LOCTEXT("PackageIOSLabel", "iOS + NSE -> Device");
}

FText FBeamPlatformNotificationsEditorModule::GetButtonTooltip() const
{
    return bDeployRunning
        ? LOCTEXT("CancelTip", "A package/deploy is running. Click to cancel it. Output is in the Output Log (LogBeamNotif).")
        : LOCTEXT("PackageIOSTip", "Pick a connected device, then package iOS, embed the Notification Service Extension, and install. Output streams to the Output Log (LogBeamNotif).");
}

FSlateIcon FBeamPlatformNotificationsEditorModule::GetButtonIcon() const
{
    return FSlateIcon(FAppStyle::GetAppStyleSetName(),
        bDeployRunning ? "GenericStop" : "MainFrame.PackageProject");
}

void FBeamPlatformNotificationsEditorModule::OnToolbarButtonClicked()
{
    if (bDeployRunning)
    {
        CancelPipeline();
    }
    else
    {
        StartPipelineFlow();
    }
}

void FBeamPlatformNotificationsEditorModule::CancelPipeline()
{
    if (DeployProcess.IsValid())
    {
        UE_LOG(LogBeamNotif, Warning, TEXT("Cancelling package/deploy..."));
        DeployProcess->Cancel(true);
    }
}

void FBeamPlatformNotificationsEditorModule::MakeScriptsExecutable()
{
#if PLATFORM_MAC
    const FString Scripts = BMN_ScriptsDir();
    const FString Args = FString::Printf(TEXT("+x \"%s\" \"%s\""),
        *(Scripts / TEXT("package-ios-deploy.sh")), *(Scripts / TEXT("add-nse.sh")));
    int32 Rc = 0; FString Out, Err;
    FPlatformProcess::ExecProcess(TEXT("/bin/chmod"), *Args, &Rc, &Out, &Err);
#endif
}

bool FBeamPlatformNotificationsEditorModule::QueryDevices(TArray<TSharedPtr<FBeamNotifDevice>>& OutDevices)
{
#if PLATFORM_MAC
    const FString TmpJson = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir() / TEXT("bmn_devices.json"));
    IFileManager::Get().Delete(*TmpJson, false, true, true);

    int32 Rc = -1; FString Out, Err;
    FPlatformProcess::ExecProcess(TEXT("/usr/bin/xcrun"),
        *FString::Printf(TEXT("devicectl list devices --json-output \"%s\""), *TmpJson), &Rc, &Out, &Err);

    FString Json;
    if (!FFileHelper::LoadFileToString(Json, *TmpJson))
    {
        return false;
    }

    TSharedPtr<FJsonObject> Root;
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        return false;
    }

    const TSharedPtr<FJsonObject>* Result = nullptr;
    if (!Root->TryGetObjectField(TEXT("result"), Result) || !Result)
    {
        return true; // valid JSON, just no devices section
    }
    const TArray<TSharedPtr<FJsonValue>>* Devices = nullptr;
    if (!(*Result)->TryGetArrayField(TEXT("devices"), Devices) || !Devices)
    {
        return true;
    }

    for (const TSharedPtr<FJsonValue>& Val : *Devices)
    {
        const TSharedPtr<FJsonObject> D = Val->AsObject();
        if (!D.IsValid()) continue;

        FString Platform, Udid, Name, State;
        const TSharedPtr<FJsonObject>* HW = nullptr;
        if (D->TryGetObjectField(TEXT("hardwareProperties"), HW) && HW)
        {
            (*HW)->TryGetStringField(TEXT("platform"), Platform);
            (*HW)->TryGetStringField(TEXT("udid"), Udid);
            (*HW)->TryGetStringField(TEXT("marketingName"), Name);
        }
        const TSharedPtr<FJsonObject>* DP = nullptr;
        if (D->TryGetObjectField(TEXT("deviceProperties"), DP) && DP)
        {
            FString N;
            if ((*DP)->TryGetStringField(TEXT("name"), N) && !N.IsEmpty()) Name = N;
        }
        const TSharedPtr<FJsonObject>* Conn = nullptr;
        if (D->TryGetObjectField(TEXT("connectionProperties"), Conn) && Conn)
        {
            (*Conn)->TryGetStringField(TEXT("tunnelState"), State);
            if (State.IsEmpty()) (*Conn)->TryGetStringField(TEXT("pairingState"), State);
        }

        const FString P = Platform.ToLower();
        if ((P == TEXT("ios") || P == TEXT("ipados")) && !Udid.IsEmpty())
        {
            TSharedPtr<FBeamNotifDevice> Dev = MakeShared<FBeamNotifDevice>();
            Dev->Udid = Udid;
            Dev->Name = Name.IsEmpty() ? TEXT("device") : Name;
            Dev->State = State.IsEmpty() ? TEXT("unknown") : State;
            OutDevices.Add(Dev);
        }
    }
    return true;
#else
    return false;
#endif
}

bool FBeamPlatformNotificationsEditorModule::ShowDevicePicker(const TArray<TSharedPtr<FBeamNotifDevice>>& Devices, FString& OutUdid)
{
    TSharedPtr<FBeamNotifDevice> Selected = Devices.Num() > 0 ? Devices[0] : nullptr;
    bool bConfirmed = false;

    TSharedRef<SWindow> Window = SNew(SWindow)
        .Title(LOCTEXT("PickTitle", "Package iOS + NSE → Device"))
        .ClientSize(FVector2D(460, 170))
        .SupportsMaximize(false)
        .SupportsMinimize(false);

    Window->SetContent(
        SNew(SBox).Padding(16.f)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 8)
            [
                SNew(STextBlock).Text(LOCTEXT("PickPrompt", "Select the device to deploy to (only connected devices can install):"))
            ]
            + SVerticalBox::Slot().AutoHeight()
            [
                SNew(SComboBox<TSharedPtr<FBeamNotifDevice>>)
                .OptionsSource(&Devices)
                .InitiallySelectedItem(Selected)
                .OnGenerateWidget_Lambda([](TSharedPtr<FBeamNotifDevice> Item)
                {
                    return SNew(STextBlock).Text(FText::FromString(Item.IsValid() ? Item->Label() : TEXT("?")));
                })
                .OnSelectionChanged_Lambda([&Selected](TSharedPtr<FBeamNotifDevice> NewSel, ESelectInfo::Type)
                {
                    if (NewSel.IsValid()) Selected = NewSel;
                })
                [
                    SNew(STextBlock).Text_Lambda([&Selected]()
                    {
                        return FText::FromString(Selected.IsValid() ? Selected->Label() : TEXT("(select a device)"));
                    })
                ]
            ]
            + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Right).Padding(0, 14, 0, 0)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot().AutoWidth().Padding(4, 0)
                [
                    SNew(SButton)
                    .Text(LOCTEXT("Cancel", "Cancel"))
                    .OnClicked_Lambda([&Window]() { Window->RequestDestroyWindow(); return FReply::Handled(); })
                ]
                + SHorizontalBox::Slot().AutoWidth().Padding(4, 0)
                [
                    SNew(SButton)
                    .Text(LOCTEXT("Go", "Package & Deploy"))
                    .OnClicked_Lambda([&Window, &bConfirmed]() { bConfirmed = true; Window->RequestDestroyWindow(); return FReply::Handled(); })
                ]
            ]
        ]);

    FSlateApplication::Get().AddModalWindow(Window, nullptr);

    if (bConfirmed && Selected.IsValid())
    {
        OutUdid = Selected->Udid;
        return true;
    }
    return false;
}

void FBeamPlatformNotificationsEditorModule::LaunchPipeline(const FString& Udid)
{
#if PLATFORM_MAC
    const FString ProjDir  = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    const FString UProject = FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath());
    const FString Target   = FPaths::GetBaseFilename(UProject); // UE convention: game target == project name
    const FString Script   = BMN_ScriptsDir() / TEXT("package-ios-deploy.sh");
    // Invoke bash on the script so the executable bit isn't required. The plugin-bundled script
    // gets all project context as args (it lives outside the project, so it can't assume paths).
    const FString Params = FString::Printf(
        TEXT("\"%s\" --project-dir \"%s\" --uproject \"%s\" --target \"%s\" --device \"%s\""),
        *Script, *ProjDir, *UProject, *Target, *Udid);

    UE_LOG(LogBeamNotif, Display, TEXT("=== iOS package + NSE + deploy -> device %s ==="), *Udid);
    UE_LOG(LogBeamNotif, Display, TEXT("Running: /bin/bash %s"), *Params);

    bPipelineOk = false;
    DeployProcess = MakeShared<FMonitoredProcess>(TEXT("/bin/bash"), Params, ProjDir, /*bHidden*/ true, /*bCreatePipes*/ true);

    DeployProcess->OnOutput().BindLambda([this](FString Line)
    {
        Line.TrimEndInline();
        if (Line.IsEmpty()) return;
        // The script prints this marker on a successful install. FMonitoredProcess can't always
        // recover bash's exit code (it returns -1), so trust the marker for success.
        if (Line.Contains(TEXT("BMN_PIPELINE_SUCCESS")))
        {
            bPipelineOk = true;
        }
        UE_LOG(LogBeamNotif, Display, TEXT("%s"), *Line);
    });

    DeployProcess->OnCompleted().BindLambda([this](int32 ReturnCode)
    {
        const bool bOk = bPipelineOk || ReturnCode == 0;
        AsyncTask(ENamedThreads::GameThread, [this, bOk, ReturnCode]()
        {
            bDeployRunning = false;
            if (bOk)
            {
                UE_LOG(LogBeamNotif, Display, TEXT("=== Done. Installed to the device. ==="));
            }
            else
            {
                UE_LOG(LogBeamNotif, Error, TEXT("=== package/deploy FAILED (exit %d) - see the log above. ==="), ReturnCode);
            }
        });
    });

    DeployProcess->OnCanceled().BindLambda([this]()
    {
        AsyncTask(ENamedThreads::GameThread, [this]()
        {
            bDeployRunning = false;
            UE_LOG(LogBeamNotif, Warning, TEXT("=== package/deploy cancelled. ==="));
        });
    });

    if (DeployProcess->Launch())
    {
        bDeployRunning = true;
    }
    else
    {
        UE_LOG(LogBeamNotif, Error, TEXT("Failed to launch the packaging process."));
        DeployProcess.Reset();
    }
#endif
}

void FBeamPlatformNotificationsEditorModule::StartPipelineFlow()
{
#if PLATFORM_MAC
    MakeScriptsExecutable();

    const FString Script = BMN_ScriptsDir() / TEXT("package-ios-deploy.sh");
    if (!FPaths::FileExists(Script))
    {
        FMessageDialog::Open(EAppMsgType::Ok,
            FText::Format(LOCTEXT("NoScript", "Script not found:\n{0}"), FText::FromString(Script)));
        return;
    }

    TArray<TSharedPtr<FBeamNotifDevice>> Devices;
    if (!QueryDevices(Devices))
    {
        FMessageDialog::Open(EAppMsgType::Ok,
            LOCTEXT("QueryFail", "Couldn't query devices via 'xcrun devicectl'. Is Xcode installed?"));
        return;
    }
    if (Devices.Num() == 0)
    {
        FMessageDialog::Open(EAppMsgType::Ok,
            LOCTEXT("NoDevices", "No iOS devices found. Connect and unlock your device, and trust this Mac."));
        return;
    }

    FString Udid;
    if (ShowDevicePicker(Devices, Udid))
    {
        LaunchPipeline(Udid);
    }
#else
    FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("MacOnly", "iOS packaging is only supported from macOS."));
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBeamPlatformNotificationsEditorModule, BeamPlatformNotificationsEditor)
