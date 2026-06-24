// iOS-only: bridge custom URL-scheme deep links (CFBundleURLSchemes, e.g. beamnotify://…)
// into the subsystem's OnDeepLink event. Notification-tap deep links do NOT come through
// here — they arrive via the Swift core's onNotificationTapped callback. This only covers
// links opened from outside a notification (Safari, Notes, another app, `xcrun simctl openurl`).

#include "BeamPlatformNotificationsNative.h"

#if PLATFORM_IOS

#include "BeamPlatformNotificationsSubsystem.h"
#include "Async/Async.h"
#include "IOS/IOSAppDelegate.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

namespace BeamNotif
{
    void IOS_RegisterOpenURLHandler()
    {
        static bool bRegistered = false;
        if (bRegistered)
        {
            return;
        }
        bRegistered = true;

        FIOSCoreDelegates::OnOpenURL.AddLambda(
            [](UIApplication* /*application*/, NSURL* url, NSString* /*sourceApplication*/, id /*annotation*/)
            {
                if (url == nullptr)
                {
                    return;
                }
                NSString* Absolute = [url absoluteString];
                const FString Link = Absolute ? FString(UTF8_TO_TCHAR([Absolute UTF8String])) : FString();
                if (Link.IsEmpty())
                {
                    return;
                }
                AsyncTask(ENamedThreads::GameThread, [Link]()
                {
                    if (UBeamPlatformNotificationsSubsystem::Active)
                    {
                        UBeamPlatformNotificationsSubsystem::Active->HandleDeepLink(Link);
                    }
                });
            });
    }
}

#endif // PLATFORM_IOS
