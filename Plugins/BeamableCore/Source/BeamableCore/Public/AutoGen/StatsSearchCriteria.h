
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "StatsSearchCriteria.generated.h"

UCLASS(BlueprintType)
class UStatsSearchCriteria : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stat")
	FString Stat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rel")
	FString Rel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value")
	FOptionalString Value;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};