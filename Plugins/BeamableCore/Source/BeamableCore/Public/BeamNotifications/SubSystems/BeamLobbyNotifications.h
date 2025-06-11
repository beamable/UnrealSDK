#pragma once

#include "Serialization/BeamJsonSerializable.h"
#include "UserSlots/UserSlot.h"
#include "BeamLobbyNotifications.generated.h"

struct FBeamContentId;
class UBeamNotifications;

UENUM(BlueprintType, Category="Beam")
enum class EBeamLobbyEvent : uint8
{  
	BEAM_LobbyCreated,
	BEAM_LobbyDisbanded,
	BEAM_DataChanged,
	BEAM_PlayerJoined,	
	BEAM_PlayerLeft,	
	BEAM_PlayerKicked,	 	
};

UCLASS(BlueprintType, Category="Beam|Enums")
class BEAMABLECORE_API UBeamLobbyEventLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (DisplayName="ContentType To Serialization Name", CompactNodeTitle = "->"), Category="Beam|Enums")
	static FString ToSerializationName(EBeamLobbyEvent Value)
	{
		const UEnum* Enum = StaticEnum<EBeamLobbyEvent>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName="Serialization Name To ContentType", CompactNodeTitle = "->"), Category="Beam|Enums")
	static EBeamLobbyEvent ToEnum(FString Value)
	{
		const UEnum* Enum = StaticEnum<EBeamLobbyEvent>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if (Value == SerializationName)
				return static_cast<EBeamLobbyEvent>(Enum->GetValueByIndex(NameIndex));
		}

		ensureAlways(false); //  This should be impossible!
		return EBeamLobbyEvent();
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FLobbyUpdateCreatedEvt
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FLobbyUpdateDisbandedEvt
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FLobbyUpdateDataChangedEvt
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FLobbyUpdatePlayerJoinedEvt
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FBeamGamerTag JoinedGamerTag;
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FLobbyUpdatePlayerLeftEvt
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FBeamGamerTag LeftGamerTag;
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FLobbyUpdatePlayerKickedEvt
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FBeamGamerTag KickedGamerTag;
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FLobbyUpdateNotificationMessage : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	EBeamLobbyEvent Type = EBeamLobbyEvent::BEAM_LobbyCreated;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FGuid LobbyId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

DECLARE_DELEGATE_OneParam(FOnLobbyUpdateNotificationCode, FLobbyUpdateNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLobbyUpdateNotification, FLobbyUpdateNotificationMessage, Evt);

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamLobbyNotifications : public UEngineSubsystem
{
	GENERATED_BODY()

	static const inline FString CTX_KEY_Lobby_Update = TEXT("lobby.update");

	UPROPERTY()
	UBeamNotifications* Notifications;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable, DisplayName="Subscribe - Lobby Update", Category="Beam", meta=(DefaultToSelf="ContextObject"))
	void SubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, const FOnLobbyUpdateNotification& Handler, UObject* ContextObject) const;

	FDelegateHandle CPP_SubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, const FOnLobbyUpdateNotificationCode& Handler, UObject* ContextObject) const;

	FDelegateHandle CPP_UnsubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, const FDelegateHandle& Handle, UObject* ContextObject) const;
};
