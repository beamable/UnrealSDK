#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeamPlatformNotificationsSubsystem.h"
#include "BeamNotifTestWidget.generated.h"

class UScrollBox;
class UVerticalBox;
class UButton;
class UTextBlock;
class UEditableTextBox;
class UBeamNotifTestSubsystem;

/// Fully code-built UMG test screen (no .uasset required) mirroring the React Native sample:
/// a Beamable connection section, native notification controls, remote-push + microservice
/// controls, deep-link controls, and a scrolling activity log. Created by
/// ABeamNotifTestPlayerController.
UCLASS()
class BEAMNOTIFTEST_API UBeamNotifTestWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UBeamNotifTestWidget(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;

    // --- Button handlers ---
    UFUNCTION() void OnConnectClicked();
    UFUNCTION() void OnRequestPermissionClicked();
    UFUNCTION() void OnFireNowClicked();
    UFUNCTION() void OnFireDelayedClicked();
    UFUNCTION() void OnRegisterRemoteClicked();
    UFUNCTION() void OnRegisterDeviceClicked();
    UFUNCTION() void OnSendToSelfClicked();
    UFUNCTION() void OnListDevicesClicked();
    UFUNCTION() void OnFireDeepLinkNotifClicked();
    UFUNCTION() void OnNavigateDetailsClicked();
    UFUNCTION() void OnCancelAllClicked();
    UFUNCTION() void OnClearLogClicked();

    // --- Native subsystem event handlers ---
    UFUNCTION() void HandlePermissionResult(bool bGranted, const FString& Status);
    UFUNCTION() void HandleTokenReceived(const FString& Token);
    UFUNCTION() void HandleTokenError(const FString& Error);
    UFUNCTION() void HandleNotificationPresented(const FBMNNotificationData& Notification);
    UFUNCTION() void HandleNotificationTapped(const FBMNNotificationData& Notification);
    UFUNCTION() void HandleDeepLink(const FString& Url);

    // --- Test subsystem event handlers ---
    UFUNCTION() void HandleTestLog(const FString& Line);
    UFUNCTION() void HandleConnectionChanged(bool bConnected);

private:
    UBeamPlatformNotificationsSubsystem* Notif() const;
    UBeamNotifTestSubsystem* Test() const;

    void BuildUI();
    UButton* AddButton(UVerticalBox* Box, const FString& Label);
    UTextBlock* AddLabel(UVerticalBox* Box, const FString& Text, int32 FontSize = 12);
    void AddSectionHeader(UVerticalBox* Box, const FString& Title);
    void AppendLog(const FString& Line);
    void RouteDeepLink(const FString& Url);

    UPROPERTY() UTextBlock* StatusText = nullptr;
    UPROPERTY() UTextBlock* TokenText = nullptr;
    UPROPERTY() UTextBlock* LogText = nullptr;
    UPROPERTY() UScrollBox* LogScroll = nullptr;
    UPROPERTY() UTextBlock* DetailsText = nullptr;
    UPROPERTY() UVerticalBox* DetailsPanel = nullptr;

    FString LastToken;
    TArray<FString> LogLines;
    bool bUIBuilt = false;
};
