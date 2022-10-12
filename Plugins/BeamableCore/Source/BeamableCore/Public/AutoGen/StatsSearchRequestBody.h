
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/StatsSearchCriteria.h"

#include "StatsSearchRequestBody.generated.h"

UCLASS(BlueprintType)
class UStatsSearchRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Domain")
	FString Domain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access")
	FString Access;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Type")
	FString ObjectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Criteria")
	TArray<UStatsSearchCriteria*> Criteria;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};