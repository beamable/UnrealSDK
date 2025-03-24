// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamNotifications/SubSystems/BeamSocialNotifications.h"

#include <string>

#include "AutoGen/OnlineStatus.h"

void FSocialRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("player"), PlayerId.AsLong);
	Serializer->WriteValue(TEXT("friend"), FriendId.AsLong);
	Serializer->WriteValue(("etype"), UBeamJsonUtils::EnumToSerializationName<EBeamFriendEventType>(EventType));
}

void FSocialRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("player"), PlayerId.AsLong);
	Serializer->WriteValue(TEXT("friend"), FriendId.AsLong);
	Serializer->WriteValue(TEXT("etype"), UBeamJsonUtils::EnumToSerializationName<EBeamFriendEventType>(EventType));
}

void FSocialRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	int64 PlayerIdLong;
	int64 FriendIdLong;
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("player")), PlayerIdLong, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("friend")), FriendIdLong, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("etype")), EventType, OuterOwner);

	PlayerId = FBeamGamerTag(PlayerIdLong);
	FriendId = FBeamGamerTag(FriendIdLong);
}


void FSocialPresenceRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("friendId"), PlayerId.AsString);
	Serializer->WriteValue(TEXT("lastOnline"), LastOnline.ToString());
	Serializer->WriteValue(TEXT("online"), Online);
	Serializer->WriteValue(TEXT("status"), Status);
	Serializer->WriteValue(TEXT("description"), Description);
}

void FSocialPresenceRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("friendId"), PlayerId.AsString);
	Serializer->WriteValue(TEXT("lastOnline"), LastOnline.ToString());
	Serializer->WriteValue(TEXT("onlineStatus"), Online);
	Serializer->WriteValue(TEXT("eventType"), Status);
	Serializer->WriteValue(TEXT("description"), Description);
}

void FSocialPresenceRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	int64 PlayerIdLong;

	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("lastOnline")), LastOnline, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("friendId")), PlayerIdLong, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("onlineStatus")), Online, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("eventType")), Status, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("description")), Description, OuterOwner);

	PlayerId = FBeamGamerTag(PlayerIdLong);
}


FSocialPresenceRefreshNotificationMessage::FSocialPresenceRefreshNotificationMessage(): Online(false)
{
}

FSocialPresenceRefreshNotificationMessage::FSocialPresenceRefreshNotificationMessage(UOnlineStatus* OnlineStatus)
{
	switch (OnlineStatus->Status.Val)
	{
	case EPresenceStatus::BEAM_Visible:
		Status = "Visible";
		break;
	case EPresenceStatus::BEAM_Away:
		Status = "Away";
		break;
	case EPresenceStatus::BEAM_Dnd:
		Status = "Dnd";
		break;
	case EPresenceStatus::BEAM_Invisible:
		Status = "Invisible";
		break;
	default:
		break;
	}
	PlayerId = OnlineStatus->PlayerId.Val;
	Description = OnlineStatus->Description.Val;
	FDateTime::Parse(*OnlineStatus->LastOnline.Val, LastOnline);
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
