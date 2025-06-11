// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamNotifications/BeamNotifications.h"
#include "Subsystems/EngineSubsystem.h"
#include "BeamPartyNotifications.generated.h"

UENUM(BlueprintType, Category="Beam")
enum class EBeamPartyEvent : uint8
{
	BEAM_PlayerJoined,
	BEAM_PlayerLeft,
	BEAM_PlayerInvited,
	BEAM_PartyUpdated,
	BEAM_PlayerPromotedToLeader,
	BEAM_PlayerKicked,
	BEAM_PlayerInviteCanceled,
	BEAM_PlayerInviteExpired
};

USTRUCT(BlueprintType, Category="Beam")
struct BEAMABLECORE_API FPartyRefreshNotificationMessage : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FGuid PartyId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	EBeamPartyEvent Type = EBeamPartyEvent::BEAM_PlayerJoined;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

DECLARE_DELEGATE_OneParam(FOnPartyRefreshNotificationCode, FPartyRefreshNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPartyRefreshNotification, FPartyRefreshNotificationMessage, Evt);

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamPartyNotifications : public UEngineSubsystem
{
	GENERATED_BODY()

	static const inline FString CTX_KEY_Party_Refresh = TEXT("party.update");

	UPROPERTY()
	UBeamNotifications* Notifications;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable, DisplayName="Subscribe - Party Refresh", Category="Beam",
		meta=(DefaultToSelf="ContextObject"))
	void SubscribeToPartyRefresh(const FUserSlot& Slot, const FName& SocketName,
	                             const FOnPartyRefreshNotification& Handler, UObject* ContextObject) const;

	FDelegateHandle CPP_SubscribeToPartyRefresh(const FUserSlot& Slot, const FName& SocketName,
	                                            const FOnPartyRefreshNotificationCode& Handler,
	                                            UObject* ContextObject) const;
};
