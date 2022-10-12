
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/EventRule.h"

#include "EventPhaseRuntime.generated.h"

UCLASS(BlueprintType)
class UEventPhaseRuntime : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time")
	int64 StartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time")
	int64 EndTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rules")
	TArray<UEventRule*> Rules;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};