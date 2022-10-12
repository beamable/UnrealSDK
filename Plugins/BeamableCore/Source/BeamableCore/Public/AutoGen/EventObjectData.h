
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Enums/EventState.h"
#include "AutoGen/Optionals/OptionalEventPhaseRuntime.h"
#include "AutoGen/Optionals/OptionalClientPermission.h"
#include "AutoGen/Event.h"
#include "AutoGen/Optionals/OptionalArrayOfEventPhaseTime.h"

#include "EventObjectData.generated.h"

UCLASS(BlueprintType)
class UEventObjectData : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight")
	FOptionalArrayOfInFlightMessage InFlight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time")
	FOptionalInt64 StartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Root Event Id")
	FOptionalString RootEventId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Origin Type")
	FOptionalString OriginType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State")
	EEventState State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Running")
	bool bRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Phase")
	FOptionalEventPhaseRuntime Phase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Permissions")
	FOptionalClientPermission Permissions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Last Child Event Id")
	FOptionalString LastChildEventId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time")
	FOptionalInt64 EndTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Origin")
	FOptionalString Origin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created At")
	FOptionalInt64 CreatedAt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content")
	UEvent* Content;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Done")
	bool bDone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leaderboard Id")
	FString LeaderboardId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Phase Times")
	FOptionalArrayOfEventPhaseTime PhaseTimes;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};