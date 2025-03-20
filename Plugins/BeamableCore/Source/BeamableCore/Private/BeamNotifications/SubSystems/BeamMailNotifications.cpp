// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamNotifications/SubSystems/BeamMailNotifications.h"

void FMailRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
}

void FMailRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
}

void FMailRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
}

void UBeamMailNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Notifications = Collection.InitializeDependency<UBeamNotifications>();
}

void UBeamMailNotifications::SubscribeToMailRefresh(const FUserSlot& Slot, const FName& SocketName,
                                                      const FOnMailRefreshNotification& Handler,
                                                      UObject* ContextObject) const
{
	FDelegateHandle Handle;

	if (!Notifications->TrySubscribeForMessage<FOnMailRefreshNotification, FMailRefreshNotificationMessage>(
		Slot, SocketName, CTX_KEY_Mail_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name,
		       *SocketName.ToString());
	}
}

FDelegateHandle UBeamMailNotifications::CPP_SubscribeToMailRefresh(const FUserSlot& Slot, const FName& SocketName,
                                                                     const FOnMailRefreshNotificationCode& Handler,
                                                                     UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnMailRefreshNotificationCode, FMailRefreshNotificationMessage>(
		Slot, SocketName, CTX_KEY_Mail_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name,
		       *SocketName.ToString());
	}
	return Handle;
}
