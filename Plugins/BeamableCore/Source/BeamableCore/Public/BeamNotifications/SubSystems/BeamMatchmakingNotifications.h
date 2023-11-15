#pragma once

#include "Serialization/BeamJsonSerializable.h"
#include "UserSlots/UserSlot.h"
#include "BeamMatchmakingNotifications.generated.h"

struct FBeamContentId;
class UBeamNotifications;

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FMatchmakingUpdateNotificationMessage : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString TicketId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString Status;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString Created;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString Expires;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	TArray<FString> Players;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString MatchType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString MatchId;
	
	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

DECLARE_DELEGATE_OneParam(FOnMatchmakingUpdateNotificationCode, FMatchmakingUpdateNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMatchmakingUpdateNotification, FMatchmakingUpdateNotificationMessage, Evt);

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FMatchmakingTimeoutNotificationMessage : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString TicketId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	TArray<FString> Players;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

DECLARE_DELEGATE_OneParam(FOnMatchmakingTimeoutNotificationCode, FMatchmakingTimeoutNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMatchmakingTimeoutNotification, FMatchmakingTimeoutNotificationMessage, Evt);

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamMatchmakingNotifications : public UEngineSubsystem
{
	GENERATED_BODY()

	static const inline FString CTX_KEY_Matchmaking_Update = TEXT("matchmaking.update.{0}");
	static const inline FString CTX_KEY_Matchmaking_Timeout = TEXT("matchmaking.timeout.{0}");

	UPROPERTY()
	UBeamNotifications* Notifications;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable, DisplayName="Subscribe - Matchmaking Update", Category="Beam")
	void SubscribeToMatchmakingUpdate(const FUserSlot& Slot, const FName& SocketName, FBeamContentId GameType, const FOnMatchmakingUpdateNotification& Handler) const;

	void CPP_SubscribeToMatchmakingUpdate(const FUserSlot& Slot, const FName& SocketName, FBeamContentId GameType, const FOnMatchmakingUpdateNotificationCode& Handler) const;

	UFUNCTION(BlueprintCallable, DisplayName="Subscribe - Matchmaking Timeout", Category="Beam")
	void SubscribeToMatchmakingTimeout(const FUserSlot& Slot, const FName& SocketName, FBeamContentId GameType, const FOnMatchmakingTimeoutNotification& Handler) const;

	void CPP_SubscribeToMatchmakingTimeout(const FUserSlot& Slot, const FName& SocketName, FBeamContentId GameType, const FOnMatchmakingTimeoutNotificationCode& Handler) const;
};
