
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "MatchMakingRanking.generated.h"

UCLASS(BlueprintType)
class UMatchMakingRanking : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gt")
	int64 Gt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank")
	int32 Rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Unranked")
	bool bIsUnranked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Variables")
	TMap<FString, FString> Variables;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};