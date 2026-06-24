#include "BeamNotifTestSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Runtime/BeamRuntime.h"
#include "RequestTracker/BeamOperation.h"

#include "AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsRegisterDeviceTokenRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsUnregisterDeviceTokenRequest.h"
#include "AutoGen/RegisterResult.h"
#include "AutoGen/UnregisterResult.h"

// These endpoints only exist once the BeamFarmMs Unreal client is regenerated (the C#
// service already exposes them as [ClientCallable]). __has_include keeps this file
// compiling before regeneration and auto-enables the buttons afterwards.
#if __has_include("AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendPushToSelfRequest.h")
  #define BEAMNOTIF_HAS_SEND 1
  #include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendPushToSelfRequest.h"
  #include "AutoGen/SendResult.h"
#else
  #define BEAMNOTIF_HAS_SEND 0
#endif

#if __has_include("AutoGen/SubSystems/BeamFarmMs/BeamFarmMsListMyDevicesRequest.h")
  #define BEAMNOTIF_HAS_LIST 1
  #include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsListMyDevicesRequest.h"
  #include "AutoGen/DeviceList.h"
  #include "AutoGen/DeviceInfo.h"
#else
  #define BEAMNOTIF_HAS_LIST 0
#endif

void UBeamNotifTestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (UBeamRuntime* Runtime = GetGameInstance()->GetSubsystem<UBeamRuntime>())
    {
        UserReadyHandle = Runtime->CPP_RegisterOnUserReady(
            FUserStateChangedHandlerCode::CreateUObject(this, &UBeamNotifTestSubsystem::HandleUserReady));
    }
}

void UBeamNotifTestSubsystem::Deinitialize()
{
    if (UBeamRuntime* Runtime = GetGameInstance() ? GetGameInstance()->GetSubsystem<UBeamRuntime>() : nullptr)
    {
        if (UserReadyHandle.IsValid())
        {
            Runtime->CPP_UnregisterOnUserReady(UserReadyHandle);
        }
    }
    Super::Deinitialize();
}

void UBeamNotifTestSubsystem::HandleUserReady(const FUserSlot& Slot)
{
    if (Slot.Name != UserSlotName)
    {
        return;
    }
    bUserReady = true;
    Log(FString::Printf(TEXT("Beamable ready · slot %s"), *Slot.Name));
    OnConnectionChanged.Broadcast(true);
}

UBeamBeamFarmMsApi* UBeamNotifTestSubsystem::GetApi()
{
    if (!BeamFarmMsApi)
    {
        BeamFarmMsApi = GEngine->GetEngineSubsystem<UBeamBeamFarmMsApi>();
    }
    return BeamFarmMsApi;
}

void UBeamNotifTestSubsystem::ConnectToBeam()
{
    UBeamRuntime* Runtime = GetGameInstance()->GetSubsystem<UBeamRuntime>();
    if (!Runtime)
    {
        Log(TEXT("BeamRuntime not available"));
        return;
    }

    // Auth calls are only valid once the SDK has started (this project has
    // bAutomaticFrictionlessAuthForOwnerPlayer=False, so there is no auto-login and the SDK may
    // still be initializing when the button is pressed). Calling login before OnStarted crashes.
    if (!Runtime->IsInitialized())
    {
        if (!bConnectRequested)
        {
            bConnectRequested = true;
            Log(TEXT("Beamable SDK still starting — will connect when ready…"));
            Runtime->CPP_RegisterOnStarted(FBeamRuntimeHandlerCode::CreateWeakLambda(this, [this]()
            {
                DoFrictionlessLogin();
            }));
            Runtime->InitSDK({}, {});
        }
        return;
    }

    DoFrictionlessLogin();
}

void UBeamNotifTestSubsystem::DoFrictionlessLogin()
{
    UBeamRuntime* Runtime = GetGameInstance() ? GetGameInstance()->GetSubsystem<UBeamRuntime>() : nullptr;
    if (!Runtime || !Runtime->IsInitialized())
    {
        Log(TEXT("Beamable SDK not initialized"));
        return;
    }

    if (Runtime->IsLoggedIn(FUserSlot{UserSlotName}))
    {
        bUserReady = true;
        Log(TEXT("Already connected to Beamable"));
        OnConnectionChanged.Broadcast(true);
        return;
    }

    Log(TEXT("Connecting to Beamable (frictionless)…"));
    Runtime->CPP_LoginFrictionlessOperation(
        FUserSlot{UserSlotName}, {},
        FBeamOperationEventHandlerCode::CreateWeakLambda(this, [this](FBeamOperationEvent Evt)
        {
            const bool bOk = Evt.EventType == EBeamOperationEventType::OET_SUCCESS;
            Log(bOk ? TEXT("Connected to Beamable") : FString::Printf(TEXT("Connect failed: %s"), *Evt.EventCode));
            OnConnectionChanged.Broadcast(bOk);
        }));
}

bool UBeamNotifTestSubsystem::IsConnected() const
{
    UBeamRuntime* Runtime = GetGameInstance() ? GetGameInstance()->GetSubsystem<UBeamRuntime>() : nullptr;
    return (Runtime && Runtime->IsInitialized()) ? Runtime->IsLoggedIn(FUserSlot{UserSlotName}) : false;
}

FString UBeamNotifTestSubsystem::GetDevicePlatform() const
{
#if PLATFORM_IOS
    return TEXT("apns");
#elif PLATFORM_ANDROID
    return TEXT("fcm");
#else
    return TEXT("none");
#endif
}

void UBeamNotifTestSubsystem::RegisterThisDevice(const FString& Token)
{
    UBeamBeamFarmMsApi* Api = GetApi();
    if (!Api) { Log(TEXT("BeamFarmMsApi not available")); return; }
    if (Token.IsEmpty()) { Log(TEXT("No push token yet — Register for remote first")); return; }

    const FString Platform = GetDevicePlatform();
#if PLATFORM_IOS
    const FString Environment = TEXT("sandbox"); // switch to "production" for App Store / TestFlight builds
#else
    const FString Environment = TEXT("production");
#endif

    UBeamFarmMsRegisterDeviceTokenRequest* Request =
        UBeamFarmMsRegisterDeviceTokenRequest::Make(Token, Environment, Platform, this, TMap<FString, FString>{});
    FBeamRequestContext Ctx;

    Api->CPP_RegisterDeviceToken(
        FUserSlot{UserSlotName}, Request,
        FOnBeamFarmMsRegisterDeviceTokenFullResponse::CreateWeakLambda(this, [this](FBeamFarmMsRegisterDeviceTokenFullResponse Response)
        {
            if (Response.State == RS_Success && Response.SuccessData)
            {
                Log(FString::Printf(TEXT("Device registered · %d device(s) · %s"),
                    Response.SuccessData->DeviceCount, *Response.SuccessData->Message));
            }
            else
            {
                Log(FString::Printf(TEXT("Register device failed: %s"),
                    Response.State == RS_Error ? *Response.ErrorData.error : TEXT("unknown")));
            }
        }),
        Ctx, FBeamOperationHandle(), this);
}

void UBeamNotifTestSubsystem::UnregisterThisDevice(const FString& Token)
{
    UBeamBeamFarmMsApi* Api = GetApi();
    if (!Api) { Log(TEXT("BeamFarmMsApi not available")); return; }

    UBeamFarmMsUnregisterDeviceTokenRequest* Request =
        UBeamFarmMsUnregisterDeviceTokenRequest::Make(Token, this, TMap<FString, FString>{});
    FBeamRequestContext Ctx;

    Api->CPP_UnregisterDeviceToken(
        FUserSlot{UserSlotName}, Request,
        FOnBeamFarmMsUnregisterDeviceTokenFullResponse::CreateWeakLambda(this, [this](FBeamFarmMsUnregisterDeviceTokenFullResponse Response)
        {
            if (Response.State == RS_Success && Response.SuccessData)
            {
                Log(FString::Printf(TEXT("Device unregistered · %d device(s) left"), Response.SuccessData->DeviceCount));
            }
            else
            {
                Log(FString::Printf(TEXT("Unregister device failed: %s"),
                    Response.State == RS_Error ? *Response.ErrorData.error : TEXT("unknown")));
            }
        }),
        Ctx, FBeamOperationHandle(), this);
}

void UBeamNotifTestSubsystem::SendPushToSelf(const FString& Title, const FString& Body, const FString& DeepLink)
{
#if BEAMNOTIF_HAS_SEND
    UBeamBeamFarmMsApi* Api = GetApi();
    if (!Api) { Log(TEXT("BeamFarmMsApi not available")); return; }

    UBeamFarmMsSendPushToSelfRequest* Request =
        UBeamFarmMsSendPushToSelfRequest::Make(Title, Body, DeepLink, this, TMap<FString, FString>{});
    FBeamRequestContext Ctx;

    Api->CPP_SendPushToSelf(
        FUserSlot{UserSlotName}, Request,
        FOnBeamFarmMsSendPushToSelfFullResponse::CreateWeakLambda(this, [this](FBeamFarmMsSendPushToSelfFullResponse Response)
        {
            if (Response.State == RS_Success && Response.SuccessData)
            {
                Log(FString::Printf(TEXT("Push sent · succeeded %d / attempted %d"),
                    Response.SuccessData->Succeeded, Response.SuccessData->Attempted));
            }
            else
            {
                Log(FString::Printf(TEXT("Send push failed: %s"),
                    Response.State == RS_Error ? *Response.ErrorData.error : TEXT("unknown")));
            }
        }),
        Ctx, FBeamOperationHandle(), this);
#else
    Log(TEXT("SendPushToSelf needs the regenerated BeamFarmMs client (see setup-unreal.sh)."));
#endif
}

void UBeamNotifTestSubsystem::ListMyDevices()
{
#if BEAMNOTIF_HAS_LIST
    UBeamBeamFarmMsApi* Api = GetApi();
    if (!Api) { Log(TEXT("BeamFarmMsApi not available")); return; }

    UBeamFarmMsListMyDevicesRequest* Request =
        UBeamFarmMsListMyDevicesRequest::Make(this, TMap<FString, FString>{});
    FBeamRequestContext Ctx;

    Api->CPP_ListMyDevices(
        FUserSlot{UserSlotName}, Request,
        FOnBeamFarmMsListMyDevicesFullResponse::CreateWeakLambda(this, [this](FBeamFarmMsListMyDevicesFullResponse Response)
        {
            if (Response.State == RS_Success && Response.SuccessData)
            {
                Log(FString::Printf(TEXT("Registered devices: %d"), Response.SuccessData->Devices.Num()));
                for (const UDeviceInfo* Device : Response.SuccessData->Devices)
                {
                    if (Device)
                    {
                        Log(FString::Printf(TEXT("  • %s (%s/%s)"), *Device->Token, *Device->Platform, *Device->Environment));
                    }
                }
            }
            else
            {
                Log(FString::Printf(TEXT("List devices failed: %s"),
                    Response.State == RS_Error ? *Response.ErrorData.error : TEXT("unknown")));
            }
        }),
        Ctx, FBeamOperationHandle(), this);
#else
    Log(TEXT("ListMyDevices needs the regenerated BeamFarmMs client (see setup-unreal.sh)."));
#endif
}

void UBeamNotifTestSubsystem::Log(const FString& Line)
{
    UE_LOG(LogTemp, Log, TEXT("[BeamNotifTest] %s"), *Line);
    OnLog.Broadcast(Line);
}
