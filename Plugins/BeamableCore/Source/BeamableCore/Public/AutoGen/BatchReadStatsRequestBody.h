
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "BatchReadStatsRequestBody.generated.h"

UCLASS(BlueprintType)
class UBatchReadStatsRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Ids")
	FString ObjectIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	FOptionalString Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Format")
	FOptionalString Format;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};