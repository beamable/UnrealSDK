// Android-only JNI bridge between the Unreal subsystem and the Beamable Kotlin core
// (shipped in beamable-notifications-release.aar). Two directions:
//
//   INBOUND  (C++ -> Kotlin): BeamNotif::Android_* call the @JvmStatic methods on
//            com.beamable.push.unreal.UnrealPush and com.beamable.deeplink.unreal.UnrealDeepLink.
//
//   OUTBOUND (Kotlin -> C++): the `Java_com_beamable_..._native*` exports implement the
//            `external fun native*` declarations in UnrealPushBridge / UnrealDeepLinkBridge.
//            Each marshals onto the game thread and forwards to UBeamPlatformNotificationsSubsystem.

#include "BeamPlatformNotificationsNative.h"

#if PLATFORM_ANDROID

#include "BeamPlatformNotificationsSubsystem.h"
#include "Async/Async.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"
#include "Android/AndroidJavaEnv.h"
#include <jni.h>

namespace
{
    const char* kPushClass     = "com/beamable/push/unreal/UnrealPush";
    const char* kDeepLinkClass = "com/beamable/deeplink/unreal/UnrealDeepLink";

    // Resolve a class through GameActivity's class loader (FindClass alone can't see
    // plugin/AAR classes from arbitrary threads).
    jclass FindClass(JNIEnv* Env, const char* Name)
    {
        if (!Env) return nullptr;
        return AndroidJavaEnv::FindJavaClassGlobalRef(Name);
    }

    void CallStaticVoid(const char* ClassName, const char* Method, const char* Sig, ...)
    {
        JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
        if (!Env) return;
        jclass Class = FindClass(Env, ClassName);
        if (!Class) return;
        jmethodID MethodId = Env->GetStaticMethodID(Class, Method, Sig);
        if (MethodId)
        {
            va_list Args;
            va_start(Args, Sig);
            Env->CallStaticVoidMethodV(Class, MethodId, Args);
            va_end(Args);
        }
        Env->DeleteGlobalRef(Class);
    }

    FString JStringToFString(JNIEnv* Env, jstring JStr)
    {
        if (!Env || !JStr) return FString();
        return FJavaHelper::FStringFromParam(Env, JStr);
    }

    // Marshal to the game thread and invoke a subsystem handler taking a single FString.
    void DispatchString(const FString& Value, void (UBeamPlatformNotificationsSubsystem::*Handler)(const FString&))
    {
        AsyncTask(ENamedThreads::GameThread, [Value, Handler]()
        {
            if (UBeamPlatformNotificationsSubsystem::Active)
            {
                (UBeamPlatformNotificationsSubsystem::Active->*Handler)(Value);
            }
        });
    }
}

// ---------------------------------------------------------------------------
// INBOUND: C++ -> Kotlin (@JvmStatic on UnrealPush / UnrealDeepLink)
// ---------------------------------------------------------------------------
namespace BeamNotif
{
    void Android_Initialize(bool bEnableRemote)
    {
        CallStaticVoid(kPushClass, "initialize", "(Z)V", (jboolean)bEnableRemote);
    }

    void Android_RegisterChannel(const FString& Id, const FString& Name, const FString& Description, int32 Importance)
    {
        JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
        if (!Env) return;
        jclass Class = FindClass(Env, kPushClass);
        if (!Class) return;
        jmethodID MethodId = Env->GetStaticMethodID(Class, "registerChannel",
            "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
        if (MethodId)
        {
            jstring JId   = Env->NewStringUTF(TCHAR_TO_UTF8(*Id));
            jstring JName = Env->NewStringUTF(TCHAR_TO_UTF8(*Name));
            jstring JDesc = Env->NewStringUTF(TCHAR_TO_UTF8(*Description));
            Env->CallStaticVoidMethod(Class, MethodId, JId, JName, JDesc, (jint)Importance);
            Env->DeleteLocalRef(JId);
            Env->DeleteLocalRef(JName);
            Env->DeleteLocalRef(JDesc);
        }
        Env->DeleteGlobalRef(Class);
    }

    void Android_RequestPermission()
    {
        CallStaticVoid(kPushClass, "requestPermission", "()V");
    }

    bool Android_HasPermission()
    {
        JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
        if (!Env) return false;
        jclass Class = FindClass(Env, kPushClass);
        if (!Class) return false;
        bool bResult = false;
        jmethodID MethodId = Env->GetStaticMethodID(Class, "hasPermission", "()Z");
        if (MethodId)
        {
            bResult = (bool)Env->CallStaticBooleanMethod(Class, MethodId);
        }
        Env->DeleteGlobalRef(Class);
        return bResult;
    }

    void Android_ScheduleLocal(const FString& Json, int64 DelayMillis)
    {
        JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
        if (!Env) return;
        jclass Class = FindClass(Env, kPushClass);
        if (!Class) return;
        jmethodID MethodId = Env->GetStaticMethodID(Class, "scheduleLocal", "(Ljava/lang/String;J)I");
        if (MethodId)
        {
            jstring JJson = Env->NewStringUTF(TCHAR_TO_UTF8(*Json));
            Env->CallStaticIntMethod(Class, MethodId, JJson, (jlong)DelayMillis);
            Env->DeleteLocalRef(JJson);
        }
        Env->DeleteGlobalRef(Class);
    }

    void Android_Cancel(int32 Id)
    {
        CallStaticVoid(kPushClass, "cancel", "(I)V", (jint)Id);
    }

    void Android_CancelAll()
    {
        CallStaticVoid(kPushClass, "cancelAll", "()V");
    }

    void Android_FetchToken()
    {
        CallStaticVoid(kPushClass, "fetchToken", "()V");
    }

    FString Android_ConsumeLaunchIntent()
    {
        JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
        if (!Env) return FString();
        jclass Class = FindClass(Env, kPushClass);
        if (!Class) return FString();
        FString Result;
        jmethodID MethodId = Env->GetStaticMethodID(Class, "consumeLaunchIntent", "()Ljava/lang/String;");
        if (MethodId)
        {
            jstring JResult = (jstring)Env->CallStaticObjectMethod(Class, MethodId);
            Result = JStringToFString(Env, JResult);
            if (JResult) Env->DeleteLocalRef(JResult);
        }
        Env->DeleteGlobalRef(Class);
        return Result;
    }

    void Android_DeepLinkInitialize()
    {
        CallStaticVoid(kDeepLinkClass, "initialize", "()V");
    }

    FString Android_GetInitialDeepLink()
    {
        JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
        if (!Env) return FString();
        jclass Class = FindClass(Env, kDeepLinkClass);
        if (!Class) return FString();
        FString Result;
        jmethodID MethodId = Env->GetStaticMethodID(Class, "getInitialLink", "()Ljava/lang/String;");
        if (MethodId)
        {
            jstring JResult = (jstring)Env->CallStaticObjectMethod(Class, MethodId);
            Result = JStringToFString(Env, JResult);
            if (JResult) Env->DeleteLocalRef(JResult);
        }
        Env->DeleteGlobalRef(Class);
        return Result;
    }
}

// ---------------------------------------------------------------------------
// OUTBOUND: Kotlin -> C++ (implements UnrealPushBridge / UnrealDeepLinkBridge externals)
// JNI looks these up by name; they must keep C linkage and exact signatures.
// ---------------------------------------------------------------------------
extern "C"
{
    JNIEXPORT void JNICALL Java_com_beamable_push_unreal_UnrealPushBridge_nativeOnToken(
        JNIEnv* Env, jobject /*thiz*/, jstring Token)
    {
        DispatchString(JStringToFString(Env, Token), &UBeamPlatformNotificationsSubsystem::HandleTokenReceivedToken);
    }

    JNIEXPORT void JNICALL Java_com_beamable_push_unreal_UnrealPushBridge_nativeOnTokenError(
        JNIEnv* Env, jobject /*thiz*/, jstring Error)
    {
        DispatchString(JStringToFString(Env, Error), &UBeamPlatformNotificationsSubsystem::HandleTokenErrorMessage);
    }

    JNIEXPORT void JNICALL Java_com_beamable_push_unreal_UnrealPushBridge_nativeOnMessageForeground(
        JNIEnv* Env, jobject /*thiz*/, jstring Json)
    {
        DispatchString(JStringToFString(Env, Json), &UBeamPlatformNotificationsSubsystem::HandleReceived);
    }

    JNIEXPORT void JNICALL Java_com_beamable_push_unreal_UnrealPushBridge_nativeOnNotificationOpened(
        JNIEnv* Env, jobject /*thiz*/, jstring Json)
    {
        DispatchString(JStringToFString(Env, Json), &UBeamPlatformNotificationsSubsystem::HandleTapped);
    }

    JNIEXPORT void JNICALL Java_com_beamable_push_unreal_UnrealPushBridge_nativeOnPermissionResult(
        JNIEnv* /*Env*/, jobject /*thiz*/, jboolean Granted)
    {
        const bool bGranted = (bool)Granted;
        AsyncTask(ENamedThreads::GameThread, [bGranted]()
        {
            if (UBeamPlatformNotificationsSubsystem::Active)
            {
                UBeamPlatformNotificationsSubsystem::Active->HandlePermissionGranted(bGranted);
            }
        });
    }

    JNIEXPORT void JNICALL Java_com_beamable_push_unreal_UnrealPushBridge_nativeOnLocalScheduled(
        JNIEnv* /*Env*/, jobject /*thiz*/, jint /*Id*/)
    {
        // No UE-facing event for scheduled-id today; ignored.
    }

    JNIEXPORT void JNICALL Java_com_beamable_push_unreal_UnrealPushBridge_nativeOnError(
        JNIEnv* Env, jobject /*thiz*/, jstring Stage, jstring Message)
    {
        const FString StageStr = JStringToFString(Env, Stage);
        const FString MessageStr = JStringToFString(Env, Message);
        AsyncTask(ENamedThreads::GameThread, [StageStr, MessageStr]()
        {
            if (UBeamPlatformNotificationsSubsystem::Active)
            {
                UBeamPlatformNotificationsSubsystem::Active->HandleError(StageStr, MessageStr);
            }
        });
    }

    JNIEXPORT void JNICALL Java_com_beamable_deeplink_unreal_UnrealDeepLinkBridge_nativeOnDeepLink(
        JNIEnv* Env, jobject /*thiz*/, jstring Url, jboolean /*IsColdStart*/)
    {
        DispatchString(JStringToFString(Env, Url), &UBeamPlatformNotificationsSubsystem::HandleDeepLink);
    }
}

#endif // PLATFORM_ANDROID
