// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamNotifications/SubSystems/BeamSocialNotifications.h"

#include <string>

#include "AutoGen/OnlineStatus.h"

void FSocialRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("player"), PlayerGamerTag.AsLong);
	Serializer->WriteValue(TEXT("friend"), FriendGamerTag.AsLong);
	Serializer->WriteValue(("etype"), UBeamJsonUtils::EnumToSerializationName<EBeamFriendEventType>(EventType));
}

void FSocialRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("player"), PlayerGamerTag.AsLong);
	Serializer->WriteValue(TEXT("friend"), FriendGamerTag.AsLong);
	Serializer->WriteValue(TEXT("etype"), UBeamJsonUtils::EnumToSerializationName<EBeamFriendEventType>(EventType));
}

void FSocialRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	int64 PlayerIdLong;
	int64 FriendIdLong;
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("player")), PlayerIdLong, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("friend")), FriendIdLong, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("etype")), EventType, OuterOwner);

	PlayerGamerTag = FBeamGamerTag(PlayerIdLong);
	FriendGamerTag = FBeamGamerTag(FriendIdLong);
}


void FSocialPresenceRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("friendId"), PlayerGamerTag.AsString);
	Serializer->WriteValue(TEXT("lastOnline"), LastOnline.ToString());
	Serializer->WriteValue(TEXT("online"), Online);
	Serializer->WriteValue(TEXT("eventType"), UBeamJsonUtils::EnumToSerializationName(Status));
	Serializer->WriteValue(TEXT("description"), Description);
}

void FSocialPresenceRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("friendId"), PlayerGamerTag.AsString);
	Serializer->WriteValue(TEXT("lastOnline"), LastOnline.ToString());
	Serializer->WriteValue(TEXT("onlineStatus"), Online);
	Serializer->WriteValue(TEXT("eventType"), UBeamJsonUtils::EnumToSerializationName(Status));
	Serializer->WriteValue(TEXT("description"), Description);
}

void FSocialPresenceRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	int64 PlayerIdLong;
	FString OnlineStatus;

	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("lastOnline")), LastOnline, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("friendId")), PlayerIdLong, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("onlineStatus")), OnlineStatus, OuterOwner);
	// UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("eventType")), Status, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("description")), Description, OuterOwner);

	PlayerGamerTag = FBeamGamerTag(PlayerIdLong);

	Online = OnlineStatus == TEXT("online");
}


FSocialPresenceRefreshNotificationMessage::FSocialPresenceRefreshNotificationMessage(): Online(false)
{
}

FSocialPresenceRefreshNotificationMessage::FSocialPresenceRefreshNotificationMessage(UOnlineStatus* OnlineStatus)
{
	Status = OnlineStatus->Status.Val;
	PlayerGamerTag = OnlineStatus->PlayerId.Val;
	Description = OnlineStatus->Description.Val;
	LastOnline = OnlineStatus->LastOnline.Val;
	Online = OnlineStatus->bOnline.Val;
}


void UBeamSocialNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Notifications = Collection.InitializeDependency<UBeamNotifications>();
}

void UBeamSocialNotifications::SubscribeToSocialRefresh(const FUserSlot& Slot, const FName& SocketName,
                                                        const FOnSocialRefreshNotification& Handler,
                                                        UObject* ContextObject) const
{
	FDelegateHandle Handle;

	if (!Notifications->TrySubscribeForMessage<FOnSocialRefreshNotification, FSocialRefreshNotificationMessage>(
		Slot, SocketName, CTX_KEY_Social_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name,
		       *SocketName.ToString());
	}
}

FDelegateHandle UBeamSocialNotifications::CPP_SubscribeToSocialRefresh(const FUserSlot& Slot, const FName& SocketName,
                                                                       const FOnSocialRefreshNotificationCode& Handler,
                                                                       UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnSocialRefreshNotificationCode, FSocialRefreshNotificationMessage>(
		Slot, SocketName, CTX_KEY_Social_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name,
		       *SocketName.ToString());
	}
	return Handle;
}

void UBeamSocialNotifications::SubscribeToSocialPresenceRefresh(const FUserSlot& Slot, const FName& SocketName,
                                                                const FOnSocialPresenceRefreshNotification& Handler,
                                                                UObject* ContextObject) const
{
	FDelegateHandle Handle;

	if (!Notifications->TrySubscribeForMessage<FOnSocialPresenceRefreshNotification,
	                                           FSocialPresenceRefreshNotificationMessage>(
		Slot, SocketName, CTX_KEY_Social_Presence_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name,
		       *SocketName.ToString());
	}
}

FDelegateHandle UBeamSocialNotifications::CPP_SubscribeToSocialPresenceRefresh(const FUserSlot& Slot,
                                                                               const FName& SocketName,
                                                                               const
                                                                               FOnSocialPresenceRefreshNotificationCode&
                                                                               Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnSocialPresenceRefreshNotificationCode,
	                                           FSocialPresenceRefreshNotificationMessage>(
		Slot, SocketName, CTX_KEY_Social_Presence_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name,
		       *SocketName.ToString());
	}
	return Handle;
}
