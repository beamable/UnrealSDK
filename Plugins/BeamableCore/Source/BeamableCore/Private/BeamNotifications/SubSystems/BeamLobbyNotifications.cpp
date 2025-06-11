#include "BeamNotifications/SubSystems/BeamLobbyNotifications.h"

#include "BeamLogging.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamNotifications/BeamNotifications.h"
#include "Serialization/BeamJsonUtils.h"

void FLobbyUpdateNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Event"), UBeamJsonUtils::EnumToSerializationName<EBeamLobbyEvent>(Type));
	Serializer->WriteValue(TEXT("Id"), LobbyId.ToString(EGuidFormats::Digits));
}

void FLobbyUpdateNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Event"), UBeamJsonUtils::EnumToSerializationName<EBeamLobbyEvent>(Type));
	Serializer->WriteValue(TEXT("Id"), LobbyId.ToString(EGuidFormats::Digits));
}

void FLobbyUpdateNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Event")), Type);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Id")), LobbyId);	
}

void UBeamLobbyNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Notifications = Collection.InitializeDependency<UBeamNotifications>();
}

void UBeamLobbyNotifications::SubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, const FOnLobbyUpdateNotification& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	const auto      Key = CTX_KEY_Lobby_Update;
	if (!Notifications->TrySubscribeForMessage<FOnLobbyUpdateNotification, FLobbyUpdateNotificationMessage>(Slot, SocketName, Key, Handler, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	else
	{
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Subscribed to message. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
}

FDelegateHandle UBeamLobbyNotifications::CPP_SubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, const FOnLobbyUpdateNotificationCode& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	const auto      Key = CTX_KEY_Lobby_Update;
	if (!Notifications->TrySubscribeForMessage<FOnLobbyUpdateNotificationCode, FLobbyUpdateNotificationMessage>(Slot, SocketName, Key, Handler, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	else
	{
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Subscribed to message. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	return Handle;
}

FDelegateHandle UBeamLobbyNotifications::CPP_UnsubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, const FDelegateHandle& Handle, UObject* ContextObject) const
{
	const auto Key = CTX_KEY_Lobby_Update;
	if (!Notifications->TryUnsubscribeFromMessage(Slot, SocketName, Key, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Failed to find the given handle so there was no need to unsubscribe. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	else
	{
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Unsubscribe from message. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	return Handle;
}
