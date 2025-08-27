#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/StatsSearchCriteria.h"
#include "Serialization/BeamJsonUtils.h"

#include "SearchExtendedRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USearchExtendedRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Domain", Category="Beam")
	FString Domain = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Type", Category="Beam")
	FString ObjectType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access", Category="Beam")
	FString Access = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Criteria", Category="Beam")
	TArray<UStatsSearchCriteria*> Criteria = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stat Keys", Category="Beam")
	TArray<FString> StatKeys = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};