
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/RewardCalendarDay.h"

#include "CalendarView.generated.h"

UCLASS(BlueprintType)
class UCalendarView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Next Index")
	int32 NextIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Next Claim Seconds")
	int64 NextClaimSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Remaining Seconds")
	int64 RemainingSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Days")
	TArray<URewardCalendarDay*> Days;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};