#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"

#include "GetMetricsUrlRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGetMetricsUrlRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Metric Name", Category="Beam")
	FString MetricName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time", Category="Beam")
	FOptionalInt64 StartTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time", Category="Beam")
	FOptionalInt64 EndTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Period", Category="Beam")
	FOptionalInt32 Period = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};