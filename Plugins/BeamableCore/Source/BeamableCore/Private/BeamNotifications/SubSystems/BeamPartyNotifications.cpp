// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamNotifications/SubSystems/BeamPartyNotifications.h"

void FPartyRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Event"), UBeamJsonUtils::EnumToSerializationName<EBeamPartyEvent>(Type));
	Serializer->WriteValue(TEXT("Id"), PartyId.ToString(EGuidFormats::Digits));
}

void FPartyRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Event"), UBeamJsonUtils::EnumToSerializationName<EBeamPartyEvent>(Type));
	Serializer->WriteValue(TEXT("Id"), PartyId.ToString(EGuidFormats::Digits));
}

void FPartyRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Event")), Type, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Id")), PartyId, OuterOwner);
}

void UBeamPartyNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Notifications = Collection.InitializeDependency<UBeamNotifications>();
}

void UBeamPartyNotifications::SubscribeToPartyRefresh(const FUserSlot& Slot, const FName& SocketName,
                                                      const FOnPartyRefreshNotification& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;

	if (!Notifications->TrySubscribeForMessage<FOnPartyRefreshNotification, FPartyRefreshNotificationMessage>(Slot, SocketName, CTX_KEY_Party_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name, *SocketName.ToString());
	}
}

FDelegateHandle UBeamPartyNotifications::CPP_SubscribeToPartyRefresh(const FUserSlot& Slot, const FName& SocketName,
	const FOnPartyRefreshNotificationCode& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnPartyRefreshNotificationCode, FPartyRefreshNotificationMessage>(Slot, SocketName, CTX_KEY_Party_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name, *SocketName.ToString());
	}
	return Handle;
}
