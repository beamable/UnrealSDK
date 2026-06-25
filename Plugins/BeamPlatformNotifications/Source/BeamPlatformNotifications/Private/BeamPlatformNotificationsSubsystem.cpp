#include "BeamPlatformNotificationsSubsystem.h"
#include "Async/Async.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "BeamPlatformNotificationsNative.h"

UBeamPlatformNotificationsSubsystem* UBeamPlatformNotificationsSubsystem::Active = nullptr;

// ---------------------------------------------------------------------------
// iOS: C ABI imported from the Swift core (see BeamableNotifications.h). On non-iOS
// platforms these are stubbed so the module still compiles for the editor.
// ---------------------------------------------------------------------------
#if PLATFORM_IOS
extern "C" {
    typedef void (*bmn_callback)(const char* json);
    void bmn_initialize();
    void bmn_requestPermission(const char* optionsJson);
    void bmn_getPermissionStatus();
    void bmn_scheduleLocal(const char* requestJson);
    void bmn_cancelLocal(const char* id);
    void bmn_cancelAllLocal();
    void bmn_getPending();
    void bmn_registerForRemote();
    void bmn_unregisterForRemote();
    void bmn_configureAuth(const char* configJson);
    void bmn_clearAuth();
    void bmn_trackOfferClicked(const char* requestJson);
    void bmn_trackOfferConverted(const char* requestJson);
    void bmn_getDeliveryReceipts();
    void bmn_registerTemplate(const char* templateJson);
    void bmn_registerCategory(const char* categoryJson);
    void bmn_setBadge(int count);
    void bmn_clearDelivered();
    const char* bmn_getLaunchNotification();
    void bmn_free(const char* ptr);
    void bmn_setOnPermissionResult(bmn_callback cb);
    void bmn_setOnTokenReceived(bmn_callback cb);
    void bmn_setOnTokenError(bmn_callback cb);
    void bmn_setOnNotificationPresented(bmn_callback cb);
    void bmn_setOnNotificationReceived(bmn_callback cb);
    void bmn_setOnNotificationTapped(bmn_callback cb);
    void bmn_setOnPendingNotifications(bmn_callback cb);
    void bmn_setOnDeliveryReceipts(bmn_callback cb);
}

// Trampolines: marshal the C string to FString and hop to the game thread before
// touching UObjects / broadcasting Blueprint delegates.
namespace
{
    void Bounce(const char* json, void (UBeamPlatformNotificationsSubsystem::*handler)(const FString&))
    {
        FString Payload = json ? UTF8_TO_TCHAR(json) : TEXT("");
        AsyncTask(ENamedThreads::GameThread, [Payload, handler]()
        {
            if (UBeamPlatformNotificationsSubsystem::Active)
            {
                (UBeamPlatformNotificationsSubsystem::Active->*handler)(Payload);
            }
        });
    }
}

static void CB_Permission(const char* j) { Bounce(j, &UBeamPlatformNotificationsSubsystem::HandlePermission); }
static void CB_TokenRecv(const char* j)  { Bounce(j, &UBeamPlatformNotificationsSubsystem::HandleTokenReceived); }
static void CB_TokenErr(const char* j)   { Bounce(j, &UBeamPlatformNotificationsSubsystem::HandleTokenError); }
static void CB_Presented(const char* j)  { Bounce(j, &UBeamPlatformNotificationsSubsystem::HandlePresented); }
static void CB_Received(const char* j)   { Bounce(j, &UBeamPlatformNotificationsSubsystem::HandleReceived); }
static void CB_Tapped(const char* j)     { Bounce(j, &UBeamPlatformNotificationsSubsystem::HandleTapped); }
static void CB_Pending(const char* j)    { Bounce(j, &UBeamPlatformNotificationsSubsystem::HandlePending); }
static void CB_Receipts(const char* j)   { Bounce(j, &UBeamPlatformNotificationsSubsystem::HandleReceipts); }
#endif // PLATFORM_IOS

// Small helper so iOS call sites stay tidy.
#if PLATFORM_IOS
  #define BMN_CALL(expr) expr
  #define BMN_CSTR(fstr) (const char*)TCHAR_TO_UTF8(*(fstr))
#else
  #define BMN_CALL(expr)
  #define BMN_CSTR(fstr) ((const char*)nullptr)
#endif

void UBeamPlatformNotificationsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    Active = this;

#if PLATFORM_IOS
    bmn_setOnPermissionResult(&CB_Permission);
    bmn_setOnTokenReceived(&CB_TokenRecv);
    bmn_setOnTokenError(&CB_TokenErr);
    bmn_setOnNotificationPresented(&CB_Presented);
    bmn_setOnNotificationReceived(&CB_Received);
    bmn_setOnNotificationTapped(&CB_Tapped);
    bmn_setOnPendingNotifications(&CB_Pending);
    bmn_setOnDeliveryReceipts(&CB_Receipts);
    bmn_initialize();
    BeamNotif::IOS_RegisterOpenURLHandler();
#elif PLATFORM_ANDROID
    // Default channel (Android 8+). Importance 4 == NotificationManager.IMPORTANCE_HIGH.
    BeamNotif::Android_Initialize(/*enableRemote*/ true);
    BeamNotif::Android_RegisterChannel(TEXT("beam_default"), TEXT("Beamable"), TEXT("Beamable notifications"), 4);
    BeamNotif::Android_DeepLinkInitialize();
    // Deliver any cold-start VIEW intent that launched the app.
    const FString InitialLink = BeamNotif::Android_GetInitialDeepLink();
    if (!InitialLink.IsEmpty())
    {
        HandleDeepLink(InitialLink);
    }
#endif

    // Capture a deep link from the notification/intent that launched the app (closed-app tap),
    // so it survives until the UI is up and can be drained via ConsumePendingDeepLink.
    FBMNNotificationData Launch;
    if (GetLaunchNotification(Launch))
    {
        if (!Launch.DeepLink.IsEmpty())
        {
            PendingDeepLink = Launch.DeepLink;
        }
    }
}

void UBeamPlatformNotificationsSubsystem::Deinitialize()
{
    if (Active == this) Active = nullptr;
    Super::Deinitialize();
}

bool UBeamPlatformNotificationsSubsystem::IsNativeSupported() const
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    return true;
#else
    return false;
#endif
}

// MARK: API

void UBeamPlatformNotificationsSubsystem::RequestPermission(bool bAlert, bool bBadge, bool bSound)
{
#if PLATFORM_IOS
    const FString Json = FString::Printf(
        TEXT("{\"alert\":%s,\"badge\":%s,\"sound\":%s}"),
        bAlert ? TEXT("true") : TEXT("false"),
        bBadge ? TEXT("true") : TEXT("false"),
        bSound ? TEXT("true") : TEXT("false"));
    bmn_requestPermission(BMN_CSTR(Json));
#elif PLATFORM_ANDROID
    BeamNotif::Android_RequestPermission();
#endif
}

void UBeamPlatformNotificationsSubsystem::GetPermissionStatus()
{
#if PLATFORM_IOS
    bmn_getPermissionStatus();
#elif PLATFORM_ANDROID
    const bool bGranted = BeamNotif::Android_HasPermission();
    HandlePermissionGranted(bGranted);
#endif
}

void UBeamPlatformNotificationsSubsystem::ScheduleLocalNotification(const FString& Id, const FString& Title,
    const FString& Body, float DelaySeconds, const FString& DeepLink, const FString& CategoryId)
{
#if PLATFORM_IOS
    // iOS LocalRequest schema: string id + trigger object.
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("id"), Id);
    Root->SetStringField(TEXT("title"), Title);
    Root->SetStringField(TEXT("body"), Body);
    if (!CategoryId.IsEmpty()) Root->SetStringField(TEXT("categoryId"), CategoryId);

    TSharedRef<FJsonObject> Trigger = MakeShared<FJsonObject>();
    if (DelaySeconds > 0.f)
    {
        Trigger->SetStringField(TEXT("type"), TEXT("timeInterval"));
        Trigger->SetNumberField(TEXT("seconds"), DelaySeconds);
        Trigger->SetBoolField(TEXT("repeats"), false);
    }
    else
    {
        Trigger->SetStringField(TEXT("type"), TEXT("immediate"));
    }
    Root->SetObjectField(TEXT("trigger"), Trigger);

    if (!DeepLink.IsEmpty())
    {
        TSharedRef<FJsonObject> UserInfo = MakeShared<FJsonObject>();
        UserInfo->SetStringField(TEXT("deepLink"), DeepLink);
        Root->SetObjectField(TEXT("userInfo"), UserInfo);
    }

    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    bmn_scheduleLocal(BMN_CSTR(Out));
#elif PLATFORM_ANDROID
    // Android NotificationTemplate schema: int id + channelId + deepLinkUrl; delay is a param.
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetNumberField(TEXT("id"), FCString::Atoi(*Id));
    Root->SetStringField(TEXT("title"), Title);
    Root->SetStringField(TEXT("body"), Body);
    Root->SetStringField(TEXT("channelId"), TEXT("beam_default"));
    if (!DeepLink.IsEmpty()) Root->SetStringField(TEXT("deepLinkUrl"), DeepLink);

    FString Out;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
    FJsonSerializer::Serialize(Root, Writer);
    BeamNotif::Android_ScheduleLocal(Out, (int64)(DelaySeconds * 1000.f));
#endif
}

void UBeamPlatformNotificationsSubsystem::ScheduleLocalJson(const FString& RequestJson)
{
#if PLATFORM_IOS
    bmn_scheduleLocal(BMN_CSTR(RequestJson));
#elif PLATFORM_ANDROID
    BeamNotif::Android_ScheduleLocal(RequestJson, 0);
#endif
}

void UBeamPlatformNotificationsSubsystem::CancelLocal(const FString& Id)
{
#if PLATFORM_IOS
    bmn_cancelLocal(BMN_CSTR(Id));
#elif PLATFORM_ANDROID
    BeamNotif::Android_Cancel(FCString::Atoi(*Id));
#endif
}

void UBeamPlatformNotificationsSubsystem::CancelAllLocal()
{
#if PLATFORM_IOS
    bmn_cancelAllLocal();
#elif PLATFORM_ANDROID
    BeamNotif::Android_CancelAll();
#endif
}

void UBeamPlatformNotificationsSubsystem::GetPending()
{
#if PLATFORM_IOS
    bmn_getPending();
#else
    // Android has no pending-list query; emit an empty array for UI parity.
    HandlePending(TEXT("[]"));
#endif
}

void UBeamPlatformNotificationsSubsystem::RegisterForRemote()
{
#if PLATFORM_IOS
    bmn_registerForRemote();
#elif PLATFORM_ANDROID
    BeamNotif::Android_FetchToken();
#endif
}

void UBeamPlatformNotificationsSubsystem::UnregisterForRemote()
{
#if PLATFORM_IOS
    bmn_unregisterForRemote();
#endif
    // Android FCM has no explicit unregister; deleting the token is handled server-side.
}

void UBeamPlatformNotificationsSubsystem::RegisterTemplateJson(const FString& TemplateJson) { BMN_CALL(bmn_registerTemplate(BMN_CSTR(TemplateJson))); }
void UBeamPlatformNotificationsSubsystem::RegisterCategoryJson(const FString& CategoryJson) { BMN_CALL(bmn_registerCategory(BMN_CSTR(CategoryJson))); }

// Beamable funnel analytics (auth + offer tracking) — dispatched per platform (iOS C ABI /
// Android JNI). The single `RequestJson` follows the canonical OfferTrackRequest shape, which
// the Android bridge splits into its (intentData, offer) pair (see UnrealPush.trackOffer*).
void UBeamPlatformNotificationsSubsystem::ConfigureAuth(const FString& AuthJson)
{
#if PLATFORM_IOS
    bmn_configureAuth(BMN_CSTR(AuthJson));
#elif PLATFORM_ANDROID
    BeamNotif::Android_ConfigureAuth(AuthJson);
#endif
}

void UBeamPlatformNotificationsSubsystem::ClearAuth()
{
#if PLATFORM_IOS
    bmn_clearAuth();
#elif PLATFORM_ANDROID
    BeamNotif::Android_ClearAuth();
#endif
}

void UBeamPlatformNotificationsSubsystem::TrackOfferClicked(const FString& RequestJson)
{
#if PLATFORM_IOS
    bmn_trackOfferClicked(BMN_CSTR(RequestJson));
#elif PLATFORM_ANDROID
    BeamNotif::Android_TrackOfferClicked(RequestJson);
#endif
}

void UBeamPlatformNotificationsSubsystem::TrackOfferConverted(const FString& RequestJson)
{
#if PLATFORM_IOS
    bmn_trackOfferConverted(BMN_CSTR(RequestJson));
#elif PLATFORM_ANDROID
    BeamNotif::Android_TrackOfferConverted(RequestJson);
#endif
}

void UBeamPlatformNotificationsSubsystem::GetDeliveryReceipts()
{
#if PLATFORM_IOS
    bmn_getDeliveryReceipts();
#else
    HandleReceipts(TEXT("[]"));
#endif
}

void UBeamPlatformNotificationsSubsystem::SetBadge(int32 Count) { BMN_CALL(bmn_setBadge((int)Count)); }
void UBeamPlatformNotificationsSubsystem::ClearDelivered() { BMN_CALL(bmn_clearDelivered()); }

bool UBeamPlatformNotificationsSubsystem::GetLaunchNotification(FBMNNotificationData& OutNotification)
{
#if PLATFORM_IOS
    const char* ptr = bmn_getLaunchNotification();
    if (!ptr) return false;
    FString Json = UTF8_TO_TCHAR(ptr);
    bmn_free(ptr);
    if (Json.IsEmpty()) return false;
    OutNotification = ParseNotification(Json);
    return true;
#elif PLATFORM_ANDROID
    const FString Json = BeamNotif::Android_ConsumeLaunchIntent();
    if (Json.IsEmpty()) return false;
    OutNotification = ParseNotification(Json);
    return true;
#else
    return false;
#endif
}

// MARK: Inbound handlers (game thread)

void UBeamPlatformNotificationsSubsystem::HandlePermission(const FString& Json)
{
    TSharedPtr<FJsonObject> Obj;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
    if (FJsonSerializer::Deserialize(Reader, Obj) && Obj.IsValid())
    {
        bool bGranted = false;
        Obj->TryGetBoolField(TEXT("granted"), bGranted);
        FString Status;
        Obj->TryGetStringField(TEXT("status"), Status);
        OnPermissionResult.Broadcast(bGranted, Status);
    }
}

void UBeamPlatformNotificationsSubsystem::HandlePermissionGranted(bool bGranted)
{
    OnPermissionResult.Broadcast(bGranted, bGranted ? TEXT("authorized") : TEXT("denied"));
}

void UBeamPlatformNotificationsSubsystem::HandleTokenReceived(const FString& Json)
{
    TSharedPtr<FJsonObject> Obj;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
    if (FJsonSerializer::Deserialize(Reader, Obj) && Obj.IsValid())
    {
        OnTokenReceived.Broadcast(Obj->GetStringField(TEXT("token")));
    }
}

void UBeamPlatformNotificationsSubsystem::HandleTokenReceivedToken(const FString& Token)
{
    OnTokenReceived.Broadcast(Token);
}

void UBeamPlatformNotificationsSubsystem::HandleTokenError(const FString& Json)
{
    TSharedPtr<FJsonObject> Obj;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
    if (FJsonSerializer::Deserialize(Reader, Obj) && Obj.IsValid())
    {
        OnTokenError.Broadcast(Obj->GetStringField(TEXT("error")));
    }
}

void UBeamPlatformNotificationsSubsystem::HandleTokenErrorMessage(const FString& Error)
{
    OnTokenError.Broadcast(Error);
}

void UBeamPlatformNotificationsSubsystem::HandlePresented(const FString& Json)
{
    const FBMNNotificationData Data = ParseNotification(Json);
    OnNotificationPresented.Broadcast(Data);
}

void UBeamPlatformNotificationsSubsystem::HandleReceived(const FString& Json)  { OnNotificationReceived.Broadcast(ParseNotification(Json)); }

void UBeamPlatformNotificationsSubsystem::HandleTapped(const FString& Json)
{
    const FBMNNotificationData Data = ParseNotification(Json);
    OnNotificationTapped.Broadcast(Data);
    // A tapped notification with a deep link is also surfaced on OnDeepLink so the UI
    // can route it through a single path.
    if (!Data.DeepLink.IsEmpty())
    {
        OnDeepLink.Broadcast(Data.DeepLink);
    }
}

void UBeamPlatformNotificationsSubsystem::HandlePending(const FString& Json)   { OnPendingNotifications.Broadcast(Json); }
void UBeamPlatformNotificationsSubsystem::HandleReceipts(const FString& Json)  { OnDeliveryReceipts.Broadcast(Json); }

void UBeamPlatformNotificationsSubsystem::HandleDeepLink(const FString& Url)
{
    if (Url.IsEmpty())
    {
        return;
    }
    // Remember it so a listener that binds slightly later (cold start) can still drain it.
    PendingDeepLink = Url;
    OnDeepLink.Broadcast(Url);
}

bool UBeamPlatformNotificationsSubsystem::ConsumePendingDeepLink(FString& OutUrl)
{
    if (PendingDeepLink.IsEmpty())
    {
        return false;
    }
    OutUrl = PendingDeepLink;
    PendingDeepLink.Reset();
    return true;
}

void UBeamPlatformNotificationsSubsystem::HandleError(const FString& Stage, const FString& Message)
{
    UE_LOG(LogTemp, Warning, TEXT("[BeamPlatformNotifications] error (%s): %s"), *Stage, *Message);
}

FBMNNotificationData UBeamPlatformNotificationsSubsystem::ParseNotification(const FString& Json)
{
    FBMNNotificationData Data;
    Data.RawJson = Json;

    TSharedPtr<FJsonObject> Obj;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
    if (FJsonSerializer::Deserialize(Reader, Obj) && Obj.IsValid())
    {
        Obj->TryGetStringField(TEXT("id"), Data.Id);
        Obj->TryGetStringField(TEXT("title"), Data.Title);
        Obj->TryGetStringField(TEXT("body"), Data.Body);
        Obj->TryGetStringField(TEXT("subtitle"), Data.Subtitle);
        Obj->TryGetStringField(TEXT("deepLink"), Data.DeepLink);
        Obj->TryGetStringField(TEXT("actionId"), Data.ActionId);
        Obj->TryGetBoolField(TEXT("wasLaunch"), Data.bWasLaunch);

        // Fall back to alternate spellings / nested locations so the deep link is found
        // regardless of where the platform/payload put it.
        auto TryKeys = [](const TSharedPtr<FJsonObject>& O, FString& Out)
        {
            if (!Out.IsEmpty() || !O.IsValid()) return;
            for (const TCHAR* Key : { TEXT("deepLink"), TEXT("deeplink"), TEXT("deep_link") })
            {
                if (O->TryGetStringField(Key, Out) && !Out.IsEmpty()) return;
            }
        };
        TryKeys(Obj, Data.DeepLink);                                   // top-level alt spellings
        const TSharedPtr<FJsonObject>* UserInfo = nullptr;
        if (Obj->TryGetObjectField(TEXT("userInfo"), UserInfo) && UserInfo)
        {
            TryKeys(*UserInfo, Data.DeepLink);                         // iOS userInfo.deepLink
        }
        const TSharedPtr<FJsonObject>* DataPayload = nullptr;
        if (Obj->TryGetObjectField(TEXT("dataPayload"), DataPayload) && DataPayload)
        {
            TryKeys(*DataPayload, Data.DeepLink);                      // Android FCM dataPayload.deeplink
        }
    }
    return Data;
}
