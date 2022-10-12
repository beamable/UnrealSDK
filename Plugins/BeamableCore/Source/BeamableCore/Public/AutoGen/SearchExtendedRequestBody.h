
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/StatsSearchCriteria.h"

#include "SearchExtendedRequestBody.generated.h"

UCLASS(BlueprintType)
class USearchExtendedRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Criteria")
	TArray<UStatsSearchCriteria*> Criteria;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Domain")
	FString Domain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Type")
	FString ObjectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stat Keys")
	TArray<FString> StatKeys;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access")
	FString Access;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};