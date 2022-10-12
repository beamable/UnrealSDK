
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfEventRule.h"

#include "EventPhase.generated.h"

UCLASS(BlueprintType)
class UEventPhase : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Duration Minutes")
	int32 DurationMinutes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Duration Millis")
	int64 DurationMillis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rules")
	FOptionalArrayOfEventRule Rules;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Duration Seconds")
	int64 DurationSeconds;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};