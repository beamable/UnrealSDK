// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamNotifications/BeamNotifications.h"
#include "BeamMailNotifications.generated.h"

USTRUCT(BlueprintType, Category="Beam")
struct BEAMABLECORE_API FMailRefreshNotificationMessage : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

DECLARE_DELEGATE_OneParam(FOnMailRefreshNotificationCode, FMailRefreshNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMailRefreshNotification, FMailRefreshNotificationMessage, Evt);

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamMailNotifications : public UEngineSubsystem
{
	GENERATED_BODY()

	static const inline FString CTX_KEY_Mail_Refresh = TEXT("mail.refresh");

	UPROPERTY()
	UBeamNotifications* Notifications;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable, DisplayName="Subscribe - Mail Refresh", Category="Beam",
		meta=(DefaultToSelf="ContextObject"))
	void SubscribeToMailRefresh(const FUserSlot& Slot, const FName& SocketName,
	                              const FOnMailRefreshNotification& Handler, UObject* ContextObject) const;

	FDelegateHandle CPP_SubscribeToMailRefresh(const FUserSlot& Slot, const FName& SocketName,
	                                             const FOnMailRefreshNotificationCode& Handler,
	                                             UObject* ContextObject) const;
};
