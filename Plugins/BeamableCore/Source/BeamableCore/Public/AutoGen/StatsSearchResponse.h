#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "StatsSearchResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UStatsSearchResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset", Category="Beam")
	int32 Offset = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	int32 Limit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Ids", Category="Beam")
	TArray<FBeamGamerTag> Ids = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Total", Category="Beam")
	FOptionalInt64 Total = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};