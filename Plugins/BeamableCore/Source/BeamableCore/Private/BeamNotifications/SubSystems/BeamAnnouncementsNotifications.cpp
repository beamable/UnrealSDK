#include "BeamNotifications/SubSystems/BeamAnnouncementsNotifications.h"

#include "BeamLogging.h"
#include "BeamNotifications/BeamNotifications.h"


void FAnnouncementRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
}

void FAnnouncementRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
}

void FAnnouncementRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
}

void UBeamAnnouncementsNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	Notifications = Collection.InitializeDependency<UBeamNotifications>();
}

void UBeamAnnouncementsNotifications::SubscribeToAnnouncementRefresh(const FUserSlot& Slot, const FName& SocketName, const FOnAnnouncementRefreshNotification& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnAnnouncementRefreshNotification, FAnnouncementRefreshNotificationMessage>(Slot, SocketName, CTX_KEY_Content_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name, *SocketName.ToString());
	}
}

FDelegateHandle UBeamAnnouncementsNotifications::CPP_SubscribeToAnnouncementRefresh(const FUserSlot& Slot, const FName& SocketName, const FOnAnnouncementRefreshNotificationCode& Handler,
                                                                                    UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnAnnouncementRefreshNotificationCode, FAnnouncementRefreshNotificationMessage>(
		Slot, SocketName, CTX_KEY_Content_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name, *SocketName.ToString());
	}
	return Handle;
}
