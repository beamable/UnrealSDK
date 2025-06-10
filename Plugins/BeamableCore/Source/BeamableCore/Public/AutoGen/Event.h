#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/EventPhase.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventGroupRewards.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalLeaderboardCohortSettings.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamClientPermission.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventRewardContent.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSchedule.h"

#include "Event.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UEvent : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date", Category="Beam")
	FString StartDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Phases", Category="Beam")
	TArray<UEventPhase*> Phases = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Partition Size", Category="Beam")
	FOptionalInt32 PartitionSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Rewards", Category="Beam")
	FOptionalEventGroupRewards GroupRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort Settings", Category="Beam")
	FOptionalLeaderboardCohortSettings CohortSettings = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Permissions", Category="Beam")
	FOptionalBeamClientPermission Permissions = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Schedule", Category="Beam")
	FOptionalSchedule Schedule = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stores", Category="Beam")
	FOptionalArrayOfString Stores = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Rewards", Category="Beam")
	FOptionalArrayOfEventRewardContent ScoreRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank Rewards", Category="Beam")
	FOptionalArrayOfEventRewardContent RankRewards = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};