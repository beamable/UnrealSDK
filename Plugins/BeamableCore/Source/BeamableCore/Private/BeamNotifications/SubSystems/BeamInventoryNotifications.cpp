#include "BeamNotifications/SubSystems/BeamInventoryNotifications.h"

#include "BeamLogging.h"
#include "BeamNotifications/BeamNotifications.h"
#include "Serialization/BeamJsonUtils.h"

void FInventoryRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString, FString>(TEXT("scopes"), Scopes, Serializer);
}

void FInventoryRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString, FString>(TEXT("scopes"), Scopes, Serializer);
}

void FInventoryRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString, FString>(Bag->GetArrayField(TEXT("scopes")), Scopes, OuterOwner);
}

void UBeamInventoryNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	Notifications = Collection.InitializeDependency<UBeamNotifications>();
}

void UBeamInventoryNotifications::SubscribeToInventoryRefresh(const FUserSlot& Slot, const FName& SocketName, const FOnInventoryRefreshNotification& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnInventoryRefreshNotification, FInventoryRefreshNotificationMessage>(Slot, SocketName, CTX_KEY_Inventory_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name, *SocketName.ToString());
	}
}

FDelegateHandle UBeamInventoryNotifications::CPP_SubscribeToInventoryRefresh(const FUserSlot& Slot, const FName& SocketName, const FOnInventoryRefreshNotificationCode& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnInventoryRefreshNotificationCode, FInventoryRefreshNotificationMessage>(Slot, SocketName, CTX_KEY_Inventory_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name, *SocketName.ToString());
	}
	return Handle;
}
