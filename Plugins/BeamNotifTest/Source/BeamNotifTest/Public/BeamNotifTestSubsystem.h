#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UserSlots/UserSlot.h"
#include "BeamNotifTestSubsystem.generated.h"

class UBeamRuntime;
class UBeamBeamFarmMsApi;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamNotifTestLog, const FString&, Line);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamNotifTestConnection, bool, bConnected);

/// Owns the Beam-side work for the notification test screen: frictionless connect and the
/// BeamFarmMs push endpoints (register/unregister device, and — once the client is
/// regenerated — send-to-self / list-devices). Modeled on UBeamFarmSubsystem so it follows
/// the project's proven request pattern. Kept separate from the native notification
/// subsystem (which needs no Beam auth) so the UI can test the library with or without login.
UCLASS()
class BEAMNOTIFTEST_API UBeamNotifTestSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /// Appends a line to the on-screen activity log (and UE_LOG).
    UPROPERTY(BlueprintAssignable, Category = "BeamNotifTest") FOnBeamNotifTestLog OnLog;
    UPROPERTY(BlueprintAssignable, Category = "BeamNotifTest") FOnBeamNotifTestConnection OnConnectionChanged;

    /// Frictionless (guest) login on the Player0 slot. No-op if already authenticated.
    UFUNCTION(BlueprintCallable, Category = "BeamNotifTest") void ConnectToBeam();

    UFUNCTION(BlueprintCallable, Category = "BeamNotifTest") bool IsConnected() const;

    /// The platform-appropriate push platform id ("apns" on iOS, "fcm" on Android, "none" otherwise).
    UFUNCTION(BlueprintCallable, Category = "BeamNotifTest") FString GetDevicePlatform() const;

    /// Registers this device's push token with BeamFarmMs (platform/environment derived from the build).
    UFUNCTION(BlueprintCallable, Category = "BeamNotifTest") void RegisterThisDevice(const FString& Token);
    UFUNCTION(BlueprintCallable, Category = "BeamNotifTest") void UnregisterThisDevice(const FString& Token);

    /// Available once the BeamFarmMs Unreal client is regenerated (see setup-unreal.sh / docs).
    UFUNCTION(BlueprintCallable, Category = "BeamNotifTest") void SendPushToSelf(const FString& Title, const FString& Body, const FString& DeepLink);
    UFUNCTION(BlueprintCallable, Category = "BeamNotifTest") void ListMyDevices();

    void Log(const FString& Line);

private:
    void HandleUserReady(const FUserSlot& Slot);
    void DoFrictionlessLogin();

    UBeamBeamFarmMsApi* GetApi();

    UPROPERTY() UBeamBeamFarmMsApi* BeamFarmMsApi = nullptr;
    FDelegateHandle UserReadyHandle;
    bool bConnectRequested = false;

    /// The owner user slot. Matches [BeamCoreSettings] RuntimeUserSlots (Player0).
    FString UserSlotName = TEXT("Player0");
    bool bUserReady = false;
};
