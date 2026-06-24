#include "BeamNotifTestWidget.h"
#include "BeamNotifTestSubsystem.h"

#include "Blueprint/WidgetTree.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "Misc/ConfigCacheIni.h"

UBeamNotifTestWidget::UBeamNotifTestWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBeamableNotificationsSubsystem* UBeamNotifTestWidget::Notif() const
{
    return GetGameInstance() ? GetGameInstance()->GetSubsystem<UBeamableNotificationsSubsystem>() : nullptr;
}

UBeamNotifTestSubsystem* UBeamNotifTestWidget::Test() const
{
    return GetGameInstance() ? GetGameInstance()->GetSubsystem<UBeamNotifTestSubsystem>() : nullptr;
}

TSharedRef<SWidget> UBeamNotifTestWidget::RebuildWidget()
{
    if (!bUIBuilt && WidgetTree)
    {
        BuildUI();
        bUIBuilt = true;
    }
    return Super::RebuildWidget();
}

void UBeamNotifTestWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (UBeamableNotificationsSubsystem* N = Notif())
    {
        N->OnPermissionResult.AddDynamic(this, &UBeamNotifTestWidget::HandlePermissionResult);
        N->OnTokenReceived.AddDynamic(this, &UBeamNotifTestWidget::HandleTokenReceived);
        N->OnTokenError.AddDynamic(this, &UBeamNotifTestWidget::HandleTokenError);
        N->OnNotificationPresented.AddDynamic(this, &UBeamNotifTestWidget::HandleNotificationPresented);
        N->OnNotificationTapped.AddDynamic(this, &UBeamNotifTestWidget::HandleNotificationTapped);
        N->OnDeepLink.AddDynamic(this, &UBeamNotifTestWidget::HandleDeepLink);

        AppendLog(N->IsNativeSupported()
            ? TEXT("Native notifications: supported on this platform")
            : TEXT("Native notifications: editor/desktop — calls are no-ops"));

        // Enable closed-app delivery analytics (POSTs each delivery to this endpoint from the
        // Notification Service Extension). Endpoint is configurable in DefaultEngine.ini.
        FString AnalyticsEndpoint;
        GConfig->GetString(TEXT("BeamableNotifications"), TEXT("AnalyticsEndpoint"), AnalyticsEndpoint, GEngineIni);
        if (!AnalyticsEndpoint.IsEmpty())
        {
            N->ConfigureAnalytics(AnalyticsEndpoint, true);
            AppendLog(TEXT("Configured delivery analytics endpoint"));
        }

        // Drain any deep link that arrived before this widget existed (cold-start push tap),
        // then fall back to the launch notification.
        FString Pending;
        if (N->ConsumePendingDeepLink(Pending))
        {
            RouteDeepLink(Pending);
        }
        else
        {
            FBMNNotificationData Launch;
            if (N->GetLaunchNotification(Launch))
            {
                AppendLog(FString::Printf(TEXT("Launched from notification: %s"),
                    Launch.DeepLink.IsEmpty() ? *Launch.Id : *Launch.DeepLink));
                if (!Launch.DeepLink.IsEmpty()) RouteDeepLink(Launch.DeepLink);
            }
        }
    }

    if (UBeamNotifTestSubsystem* T = Test())
    {
        T->OnLog.AddDynamic(this, &UBeamNotifTestWidget::HandleTestLog);
        T->OnConnectionChanged.AddDynamic(this, &UBeamNotifTestWidget::HandleConnectionChanged);
        HandleConnectionChanged(T->IsConnected());
    }
}

void UBeamNotifTestWidget::NativeDestruct()
{
    if (UBeamableNotificationsSubsystem* N = Notif())
    {
        N->OnPermissionResult.RemoveAll(this);
        N->OnTokenReceived.RemoveAll(this);
        N->OnTokenError.RemoveAll(this);
        N->OnNotificationPresented.RemoveAll(this);
        N->OnNotificationTapped.RemoveAll(this);
        N->OnDeepLink.RemoveAll(this);
    }
    if (UBeamNotifTestSubsystem* T = Test())
    {
        T->OnLog.RemoveAll(this);
        T->OnConnectionChanged.RemoveAll(this);
    }
    Super::NativeDestruct();
}

// ---------------------------------------------------------------------------
// UI construction
// ---------------------------------------------------------------------------
UTextBlock* UBeamNotifTestWidget::AddLabel(UVerticalBox* Box, const FString& Text, int32 FontSize)
{
    UTextBlock* Label = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
    Label->SetText(FText::FromString(Text));
    FSlateFontInfo Font = Label->GetFont();
    Font.Size = FontSize;
    Label->SetFont(Font);
    Label->SetAutoWrapText(true);
    if (UVerticalBoxSlot* Slot = Box->AddChildToVerticalBox(Label))
    {
        Slot->SetPadding(FMargin(0.f, 2.f));
    }
    return Label;
}

void UBeamNotifTestWidget::AddSectionHeader(UVerticalBox* Box, const FString& Title)
{
    UTextBlock* Header = AddLabel(Box, Title, 16);
    Header->SetColorAndOpacity(FSlateColor(FLinearColor(0.55f, 0.4f, 1.f)));
}

UButton* UBeamNotifTestWidget::AddButton(UVerticalBox* Box, const FString& Label)
{
    UButton* Button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
    UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
    Text->SetText(FText::FromString(Label));
    Button->AddChild(Text);
    if (UVerticalBoxSlot* Slot = Box->AddChildToVerticalBox(Button))
    {
        Slot->SetPadding(FMargin(0.f, 3.f));
    }
    return Button;
}

void UBeamNotifTestWidget::BuildUI()
{
    UScrollBox* Root = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass());
    WidgetTree->RootWidget = Root;

    UVerticalBox* Box = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
    Root->AddChild(Box);

    AddLabel(Box, TEXT("Beamable Notifications — Native Test"), 20);

    // 1) Beamable connection
    AddSectionHeader(Box, TEXT("Beamable"));
    StatusText = AddLabel(Box, TEXT("Status: not connected"));
    AddButton(Box, TEXT("Connect to Beamable"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnConnectClicked);

    // 2) Native notifications
    AddSectionHeader(Box, TEXT("Notifications (native iOS/Android)"));
    AddButton(Box, TEXT("Request permission"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnRequestPermissionClicked);
    AddButton(Box, TEXT("Fire now → #777"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnFireNowClicked);
    AddButton(Box, TEXT("Fire in 10s → #888"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnFireDelayedClicked);
    AddButton(Box, TEXT("Register for remote (APNs/FCM)"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnRegisterRemoteClicked);
    AddButton(Box, TEXT("Cancel all local"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnCancelAllClicked);

    // 3) Remote push (microservice)
    AddSectionHeader(Box, TEXT("Remote push (BeamFarmMs microservice)"));
    TokenText = AddLabel(Box, TEXT("Token: none yet (Register for remote first)"));
    AddButton(Box, TEXT("Register this device"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnRegisterDeviceClicked);
    AddButton(Box, TEXT("Send push to myself"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnSendToSelfClicked);
    AddButton(Box, TEXT("List my registered devices"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnListDevicesClicked);

    // 4) Deep links
    AddSectionHeader(Box, TEXT("Deep links"));
    AddButton(Box, TEXT("Fire notification → beamfarm://details/123"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnFireDeepLinkNotifClicked);
    AddButton(Box, TEXT("Navigate directly → Details #55"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnNavigateDetailsClicked);

    // Deep-link target panel (hidden until a deep link arrives).
    DetailsPanel = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
    Box->AddChildToVerticalBox(DetailsPanel);
    DetailsText = AddLabel(DetailsPanel, TEXT(""), 14);
    DetailsText->SetColorAndOpacity(FSlateColor(FLinearColor(0.35f, 0.85f, 0.45f)));
    DetailsPanel->SetVisibility(ESlateVisibility::Collapsed);

    // 5) Activity log
    AddSectionHeader(Box, TEXT("Activity log"));
    AddButton(Box, TEXT("Clear log"))->OnClicked.AddDynamic(this, &UBeamNotifTestWidget::OnClearLogClicked);
    LogScroll = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass());
    if (UVerticalBoxSlot* LogSlot = Box->AddChildToVerticalBox(LogScroll))
    {
        LogSlot->SetPadding(FMargin(0.f, 4.f));
    }
    LogText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
    LogText->SetAutoWrapText(true);
    LogScroll->AddChild(LogText);
}

// ---------------------------------------------------------------------------
// Button handlers
// ---------------------------------------------------------------------------
void UBeamNotifTestWidget::OnConnectClicked()
{
    if (UBeamNotifTestSubsystem* T = Test()) T->ConnectToBeam();
}

void UBeamNotifTestWidget::OnRequestPermissionClicked()
{
    if (UBeamableNotificationsSubsystem* N = Notif()) N->RequestPermission(true, true, true);
}

void UBeamNotifTestWidget::OnFireNowClicked()
{
    if (UBeamableNotificationsSubsystem* N = Notif())
    {
        N->ScheduleLocalNotification(TEXT("777"), TEXT("Details #777"), TEXT("Fired immediately from Unreal"), 0.f);
        AppendLog(TEXT("Scheduled immediate notification #777"));
    }
}

void UBeamNotifTestWidget::OnFireDelayedClicked()
{
    if (UBeamableNotificationsSubsystem* N = Notif())
    {
        N->ScheduleLocalNotification(TEXT("888"), TEXT("Details #888"), TEXT("Background & tap me"), 10.f);
        AppendLog(TEXT("Scheduled notification #888 in 10s"));
    }
}

void UBeamNotifTestWidget::OnRegisterRemoteClicked()
{
    if (UBeamableNotificationsSubsystem* N = Notif())
    {
        N->RegisterForRemote();
        AppendLog(TEXT("Requested remote registration (APNs/FCM)…"));
    }
}

void UBeamNotifTestWidget::OnRegisterDeviceClicked()
{
    if (UBeamNotifTestSubsystem* T = Test()) T->RegisterThisDevice(LastToken);
}

void UBeamNotifTestWidget::OnSendToSelfClicked()
{
    if (UBeamNotifTestSubsystem* T = Test())
        T->SendPushToSelf(TEXT("Hello from Unreal"), TEXT("Remote push to self"), TEXT("beamfarm://details/999"));
}

void UBeamNotifTestWidget::OnListDevicesClicked()
{
    if (UBeamNotifTestSubsystem* T = Test()) T->ListMyDevices();
}

void UBeamNotifTestWidget::OnFireDeepLinkNotifClicked()
{
    if (UBeamableNotificationsSubsystem* N = Notif())
    {
        N->ScheduleLocalNotification(TEXT("123"), TEXT("Deep link"), TEXT("Tap to open Details #123"),
            0.f, TEXT("beamfarm://details/123"));
        AppendLog(TEXT("Scheduled deep-link notification → beamfarm://details/123"));
    }
}

void UBeamNotifTestWidget::OnNavigateDetailsClicked()
{
    RouteDeepLink(TEXT("beamfarm://details/55"));
}

void UBeamNotifTestWidget::OnCancelAllClicked()
{
    if (UBeamableNotificationsSubsystem* N = Notif())
    {
        N->CancelAllLocal();
        AppendLog(TEXT("Cancelled all local notifications"));
    }
}

void UBeamNotifTestWidget::OnClearLogClicked()
{
    LogLines.Reset();
    if (LogText) LogText->SetText(FText::GetEmpty());
}

// ---------------------------------------------------------------------------
// Native subsystem events
// ---------------------------------------------------------------------------
void UBeamNotifTestWidget::HandlePermissionResult(bool bGranted, const FString& Status)
{
    AppendLog(FString::Printf(TEXT("Permission: %s (%s)"), bGranted ? TEXT("granted") : TEXT("denied"), *Status));
}

void UBeamNotifTestWidget::HandleTokenReceived(const FString& Token)
{
    LastToken = Token;
    const FString Short = Token.Len() > 12 ? Token.Left(12) + TEXT("…") : Token;
    if (TokenText) TokenText->SetText(FText::FromString(FString::Printf(TEXT("Token: %s"), *Short)));
    AppendLog(FString::Printf(TEXT("Push token: %s"), *Short));
}

void UBeamNotifTestWidget::HandleTokenError(const FString& Error)
{
    AppendLog(FString::Printf(TEXT("Push token error: %s"), *Error));
}

void UBeamNotifTestWidget::HandleNotificationPresented(const FBMNNotificationData& Notification)
{
    AppendLog(FString::Printf(TEXT("Presented (foreground): %s"), *Notification.Title));
}

void UBeamNotifTestWidget::HandleNotificationTapped(const FBMNNotificationData& Notification)
{
    AppendLog(FString::Printf(TEXT("Tapped: %s → %s"), *Notification.Title,
        Notification.DeepLink.IsEmpty() ? *Notification.Id : *Notification.DeepLink));
    // Route here directly too (in addition to OnDeepLink) so a tapped notification always navigates.
    if (!Notification.DeepLink.IsEmpty())
    {
        RouteDeepLink(Notification.DeepLink);
    }
}

void UBeamNotifTestWidget::HandleDeepLink(const FString& Url)
{
    AppendLog(FString::Printf(TEXT("Deep link: %s"), *Url));
    RouteDeepLink(Url);
}

// ---------------------------------------------------------------------------
// Test subsystem events
// ---------------------------------------------------------------------------
void UBeamNotifTestWidget::HandleTestLog(const FString& Line)
{
    AppendLog(Line);
}

void UBeamNotifTestWidget::HandleConnectionChanged(bool bConnected)
{
    if (StatusText)
    {
        StatusText->SetText(FText::FromString(bConnected ? TEXT("Status: connected") : TEXT("Status: not connected")));
        StatusText->SetColorAndOpacity(FSlateColor(bConnected ? FLinearColor(0.35f, 0.85f, 0.45f) : FLinearColor::Gray));
    }
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------
void UBeamNotifTestWidget::AppendLog(const FString& Line)
{
    const FString Stamped = FString::Printf(TEXT("%s  %s"), *FDateTime::Now().ToString(TEXT("%H:%M:%S")), *Line);
    LogLines.Add(Stamped);
    while (LogLines.Num() > 60)
    {
        LogLines.RemoveAt(0);
    }
    if (LogText)
    {
        LogText->SetText(FText::FromString(FString::Join(LogLines, TEXT("\n"))));
    }
    if (LogScroll)
    {
        LogScroll->ScrollToEnd();
    }
}

void UBeamNotifTestWidget::RouteDeepLink(const FString& Url)
{
    // Parse a details id out of beamfarm://details/<id> (or any …/details/<id>).
    FString Id;
    int32 Index = INDEX_NONE;
    const FString Marker = TEXT("details/");
    if (Url.FindLastChar('/', Index))
    {
        Id = Url.RightChop(Index + 1);
    }
    if (Url.Contains(Marker))
    {
        int32 MarkerPos = Url.Find(Marker, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
        Id = Url.RightChop(MarkerPos + Marker.Len());
    }

    if (DetailsPanel && DetailsText)
    {
        DetailsPanel->SetVisibility(ESlateVisibility::Visible);
        DetailsText->SetText(FText::FromString(FString::Printf(TEXT("DEEP LINK TARGET — Details id = %s"), *Id)));
    }
    AppendLog(FString::Printf(TEXT("Routed to Details #%s"), *Id));
}
