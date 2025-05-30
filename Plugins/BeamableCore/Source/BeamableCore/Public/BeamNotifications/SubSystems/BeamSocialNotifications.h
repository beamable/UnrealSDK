// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/OnlineStatus.h"
#include "BeamNotifications/BeamNotifications.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Subsystems/EngineSubsystem.h"
#include "BeamSocialNotifications.generated.h"

UENUM(BlueprintType, Category="Beam")
enum class EBeamFriendEventType : uint8
{
	BEAM_friend,
	BEAM_unfriend,
	BEAM_block,
	BEAM_unblock,
	BEAM_mute,
	BEAM_unmute
};


USTRUCT(BlueprintType, Category="Beam")
struct BEAMABLECORE_API FSocialRefreshNotificationMessage : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
	FBeamGamerTag PlayerGamerTag;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
	FBeamGamerTag FriendGamerTag;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
	EBeamFriendEventType EventType = EBeamFriendEventType::BEAM_friend;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

USTRUCT(BlueprintType, Category="Beam")
struct BEAMABLECORE_API FSocialPresenceRefreshNotificationMessage : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
	FBeamGamerTag PlayerGamerTag;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
	bool Online;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
	FDateTime LastOnline;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
	EBeamPresenceStatus Status = EBeamPresenceStatus::BEAM_Invisible;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Beam")
	FString Description;

	FSocialPresenceRefreshNotificationMessage();

	FSocialPresenceRefreshNotificationMessage(UOnlineStatus* OnlineStatus);

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};


DECLARE_DELEGATE_OneParam(FOnSocialRefreshNotificationCode, FSocialRefreshNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSocialRefreshNotification, FSocialRefreshNotificationMessage, Evt);

DECLARE_DELEGATE_OneParam(FOnSocialPresenceRefreshNotificationCode, FSocialPresenceRefreshNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSocialPresenceRefreshNotification, FSocialPresenceRefreshNotificationMessage, Evt);

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamSocialNotifications : public UEngineSubsystem
{
	GENERATED_BODY()
	static const inline FString CTX_KEY_Social_Refresh = TEXT("SOCIAL.UPDATE");
	static const inline FString CTX_KEY_Social_Presence_Refresh = TEXT("social.friend_presence_changed");

	UPROPERTY()
	UBeamNotifications* Notifications;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	/**
	 * @brief Subscribe to any updates on the Social.
	 * Social is the data that tells any updates on the friends list like delete, add a friend.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Subscribe - Social Refresh", Category="Beam",
		meta=(DefaultToSelf="ContextObject"))
	void SubscribeToSocialRefresh(const FUserSlot& Slot, const FName& SocketName,
	                              const FOnSocialRefreshNotification& Handler, UObject* ContextObject) const;

	FDelegateHandle CPP_SubscribeToSocialRefresh(const FUserSlot& Slot, const FName& SocketName,
	                                             const FOnSocialRefreshNotificationCode& Handler,
	                                             UObject* ContextObject) const;

	/**
	 * @brief Subscribe to any updates on the Social Presence.
	 * Social Presence is the data that tells the friends status (Online, Offline)
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Subscribe - Social Presence Refresh", Category="Beam",
		meta=(DefaultToSelf="ContextObject"))
	void SubscribeToSocialPresenceRefresh(const FUserSlot& Slot, const FName& SocketName,
	                                      const FOnSocialPresenceRefreshNotification& Handler,
	                                      UObject* ContextObject) const;

	/**
	 * @copydoc SubscribeToSocialPresenceRefresh
	 */
	FDelegateHandle CPP_SubscribeToSocialPresenceRefresh(const FUserSlot& Slot, const FName& SocketName,
	                                                     const FOnSocialPresenceRefreshNotificationCode& Handler,
	                                                     UObject* ContextObject) const;
};
