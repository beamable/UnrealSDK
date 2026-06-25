#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BeamPlatformNotificationsSubsystem.generated.h"

/// Normalized notification payload delivered to Blueprints. `RawJson` carries the full
/// payload (including arbitrary userInfo) for advanced use; common fields are lifted out.
USTRUCT(BlueprintType)
struct FBMNNotificationData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Notifications") FString Id;
    UPROPERTY(BlueprintReadOnly, Category = "Notifications") FString Title;
    UPROPERTY(BlueprintReadOnly, Category = "Notifications") FString Body;
    UPROPERTY(BlueprintReadOnly, Category = "Notifications") FString Subtitle;
    UPROPERTY(BlueprintReadOnly, Category = "Notifications") FString DeepLink;
    UPROPERTY(BlueprintReadOnly, Category = "Notifications") FString ActionId;
    UPROPERTY(BlueprintReadOnly, Category = "Notifications") bool bWasLaunch = false;
    UPROPERTY(BlueprintReadOnly, Category = "Notifications") FString RawJson;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBMNOnPermissionResult, bool, bGranted, const FString&, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBMNOnString, const FString&, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBMNOnNotification, const FBMNNotificationData&, Notification);

/// Blueprint-facing API and event hub for BeamableNotifications. As a
/// UGameInstanceSubsystem it has a clear lifetime and is easy to reach from Blueprints
/// via "Get Game Instance Subsystem".
///
/// Platform routing:
///   * iOS     — calls the Swift core's C ABI (`bmn_*`); callbacks arrive via C trampolines.
///   * Android — calls the Kotlin core via JNI (`UnrealPush`/`UnrealDeepLink`); callbacks
///               arrive via the `Java_..._native*` exports in BeamPlatformNotificationsAndroid.cpp.
///   * Editor / desktop — no-ops, so the module still compiles and the UI can be wired.
UCLASS()
class BEAMPLATFORMNOTIFICATIONS_API UBeamPlatformNotificationsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // Events (feature 3)
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnPermissionResult OnPermissionResult;
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnString OnTokenReceived;
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnString OnTokenError;
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnNotification OnNotificationPresented;
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnNotification OnNotificationReceived;
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnNotification OnNotificationTapped;
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnString OnPendingNotifications;
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnString OnDeliveryReceipts;

    /// Fired for URL-scheme deep links that did NOT come through a notification tap
    /// (e.g. `beamnotify://details/123` opened from the browser, an `adb` VIEW intent, or
    /// an Android cold/warm-start launch). Notification-tap deep links arrive on
    /// `OnNotificationTapped` (see `FBMNNotificationData::DeepLink`).
    UPROPERTY(BlueprintAssignable, Category = "Notifications") FBMNOnString OnDeepLink;

    // Permission (feature 5)
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    void RequestPermission(bool bAlert = true, bool bBadge = true, bool bSound = true);

    UFUNCTION(BlueprintCallable, Category = "Notifications")
    void GetPermissionStatus();

    // Local notifications (feature 1)
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    void ScheduleLocalNotification(const FString& Id, const FString& Title, const FString& Body,
                                   float DelaySeconds = 0.f, const FString& DeepLink = TEXT(""),
                                   const FString& CategoryId = TEXT(""));

    /// Advanced: schedule from a full LocalRequest JSON string (see docs for the schema).
    /// iOS expects the LocalRequest schema; Android expects the NotificationTemplate schema.
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    void ScheduleLocalJson(const FString& RequestJson);

    UFUNCTION(BlueprintCallable, Category = "Notifications") void CancelLocal(const FString& Id);
    UFUNCTION(BlueprintCallable, Category = "Notifications") void CancelAllLocal();
    UFUNCTION(BlueprintCallable, Category = "Notifications") void GetPending();

    // Remote notifications (feature 2)
    UFUNCTION(BlueprintCallable, Category = "Notifications") void RegisterForRemote();
    UFUNCTION(BlueprintCallable, Category = "Notifications") void UnregisterForRemote();

    // Templates / categories (features 4, 7, 8) — iOS only; Android no-ops.
    UFUNCTION(BlueprintCallable, Category = "Notifications") void RegisterTemplateJson(const FString& TemplateJson);
    UFUNCTION(BlueprintCallable, Category = "Notifications") void RegisterCategoryJson(const FString& CategoryJson);
    UFUNCTION(BlueprintCallable, Category = "Notifications") void GetDeliveryReceipts();

    // Beamable funnel analytics (auth + offer tracking) — works on iOS and Android.

    /// Persist the player's bearer token + realm routing so the native code can authenticate
    /// the funnel POSTs (Clicked/Converted) even when the engine VM is asleep. Call on
    /// login/refresh. `AuthJson` is the canonical AuthConfig:
    /// {"accessToken":"","refreshToken":"","accessTokenExpiresAt":<epoch-ms>,"cid":"","pid":"","host":"https://..."}.
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    void ConfigureAuth(const FString& AuthJson);

    /// Clear the persisted auth credentials. Call on logout.
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    void ClearAuth();

    /// Emit a "Clicked" funnel event for an offer the player acted on, attributed back to the
    /// originating campaign. `RequestJson` is the canonical OfferTrackRequest:
    /// {"campaignId":"","nodeId":"","gamerTag":"","accountId":"","cidPid":"","deeplink":"","offer":{...}}.
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    void TrackOfferClicked(const FString& RequestJson);

    /// Emit a "Converted" funnel event for an offer conversion. Same OfferTrackRequest shape as
    /// TrackOfferClicked.
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    void TrackOfferConverted(const FString& RequestJson);

    // Badge — iOS only; Android no-ops.
    UFUNCTION(BlueprintCallable, Category = "Notifications") void SetBadge(int32 Count);
    UFUNCTION(BlueprintCallable, Category = "Notifications") void ClearDelivered();

    // Get intent (feature 6) — the notification (iOS) / VIEW intent (Android) that launched the app.
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    bool GetLaunchNotification(FBMNNotificationData& OutNotification);

    /// Returns (and clears) a deep link that arrived before any listener was bound — e.g. a
    /// cold-start push tap that fires during early subsystem init, before the UI exists.
    /// UI should call this on construct in addition to binding OnDeepLink, so no link is missed.
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    bool ConsumePendingDeepLink(FString& OutUrl);

    /// True on platforms with a real native backend (iOS / Android). Useful so the UI can
    /// show "native calls are no-ops in the editor".
    UFUNCTION(BlueprintCallable, Category = "Notifications")
    bool IsNativeSupported() const;

    /// The active instance, used by the C-callback / JNI trampolines. Set in Initialize.
    static UBeamPlatformNotificationsSubsystem* Active;

    // Internal: invoked (on the game thread) by the native callback trampolines.
    void HandlePermission(const FString& Json);
    void HandlePermissionGranted(bool bGranted);
    void HandleTokenReceived(const FString& Json);
    void HandleTokenReceivedToken(const FString& Token);
    void HandleTokenError(const FString& Json);
    void HandleTokenErrorMessage(const FString& Error);
    void HandlePresented(const FString& Json);
    void HandleReceived(const FString& Json);
    void HandleTapped(const FString& Json);
    void HandlePending(const FString& Json);
    void HandleReceipts(const FString& Json);
    void HandleDeepLink(const FString& Url);
    void HandleError(const FString& Stage, const FString& Message);

    static FBMNNotificationData ParseNotification(const FString& Json);

private:
    /// A deep link captured before any OnDeepLink listener existed (cold-start tap). Drained
    /// by ConsumePendingDeepLink.
    FString PendingDeepLink;
};
