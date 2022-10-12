
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "GetMetricsUrlRequestBody.generated.h"

UCLASS(BlueprintType)
class UGetMetricsUrlRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time")
	FOptionalInt64 StartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name")
	FString ServiceName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Metric Name")
	FString MetricName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time")
	FOptionalInt64 EndTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Period")
	FOptionalInt32 Period;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};