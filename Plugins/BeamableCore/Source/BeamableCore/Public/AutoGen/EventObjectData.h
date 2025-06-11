#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamEventState.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventPhaseRuntime.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamClientPermission.h"
#include "BeamableCore/Public/AutoGen/Event.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventPhaseTime.h"

#include "EventObjectData.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UEventObjectData : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Done", Category="Beam")
	bool bDone = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Running", Category="Beam")
	bool bRunning = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State", Category="Beam")
	EBeamEventState State = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leaderboard Id", Category="Beam")
	FString LeaderboardId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content", Category="Beam")
	UEvent* Content = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Last Child Event Id", Category="Beam")
	FOptionalString LastChildEventId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time", Category="Beam")
	FOptionalInt64 StartTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Root Event Id", Category="Beam")
	FOptionalString RootEventId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Origin Type", Category="Beam")
	FOptionalString OriginType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Phase", Category="Beam")
	FOptionalEventPhaseRuntime Phase = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Permissions", Category="Beam")
	FOptionalBeamClientPermission Permissions = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time", Category="Beam")
	FOptionalInt64 EndTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Origin", Category="Beam")
	FOptionalString Origin = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created At", Category="Beam")
	FOptionalInt64 CreatedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight", Category="Beam")
	FOptionalArrayOfInFlightMessage InFlight = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Phase Times", Category="Beam")
	FOptionalArrayOfEventPhaseTime PhaseTimes = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};