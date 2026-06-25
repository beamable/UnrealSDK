#pragma once

#include "CoreMinimal.h"

/// Platform-specific native entry points used by UBeamPlatformNotificationsSubsystem.
/// Implementations live in:
///   * IOS/BeamPlatformNotificationsIOS.cpp     (iOS URL-scheme deep links)
///   * Android/BeamPlatformNotificationsAndroid.cpp (JNI to the Kotlin core)
/// On editor / desktop these are not referenced (the subsystem guards every call site
/// with PLATFORM_IOS / PLATFORM_ANDROID), so no stub bodies are needed off-device.
namespace BeamNotif
{
#if PLATFORM_IOS
    /// Subscribe to UE's iOS "open URL" delegate so custom-scheme deep links
    /// (CFBundleURLSchemes) are forwarded to the subsystem's OnDeepLink event.
    void IOS_RegisterOpenURLHandler();
#endif

#if PLATFORM_ANDROID
    void    Android_Initialize(bool bEnableRemote);
    void    Android_RegisterChannel(const FString& Id, const FString& Name, const FString& Description, int32 Importance);
    void    Android_RequestPermission();
    bool    Android_HasPermission();
    void    Android_ScheduleLocal(const FString& Json, int64 DelayMillis);
    void    Android_Cancel(int32 Id);
    void    Android_CancelAll();
    void    Android_FetchToken();
    FString Android_ConsumeLaunchIntent();

    // Beamable funnel analytics (auth + offer tracking) — calls the UnrealPush @JvmStatic methods.
    void    Android_ConfigureAuth(const FString& AuthJson);
    void    Android_ClearAuth();
    void    Android_TrackOfferClicked(const FString& RequestJson);
    void    Android_TrackOfferConverted(const FString& RequestJson);

    // Deep links (com.beamable.deeplink.unreal.UnrealDeepLink)
    void    Android_DeepLinkInitialize();
    FString Android_GetInitialDeepLink();
#endif
}
