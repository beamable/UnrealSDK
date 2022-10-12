
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/EventPhase.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalEventGroupRewards.h"
#include "AutoGen/Optionals/OptionalLeaderboardCohortSettings.h"
#include "AutoGen/Optionals/OptionalClientPermission.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfEventRewardContent.h"
#include "AutoGen/Optionals/OptionalSchedule.h"

#include "Event.generated.h"

UCLASS(BlueprintType)
class UEvent : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date")
	FString StartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Phases")
	TArray<UEventPhase*> Phases;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Partition Size")
	FOptionalInt32 PartitionSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Rewards")
	FOptionalEventGroupRewards GroupRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort Settings")
	FOptionalLeaderboardCohortSettings CohortSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Permissions")
	FOptionalClientPermission Permissions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stores")
	FOptionalArrayOfString Stores;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Rewards")
	FOptionalArrayOfEventRewardContent ScoreRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Schedule")
	FOptionalSchedule Schedule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank Rewards")
	FOptionalArrayOfEventRewardContent RankRewards;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};