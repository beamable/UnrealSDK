#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "BatchReadStatsRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBatchReadStatsRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Ids", Category="Beam")
	FBeamStatsType ObjectIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats", Category="Beam")
	FOptionalString Stats = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Format", Category="Beam")
	FOptionalString Format = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};