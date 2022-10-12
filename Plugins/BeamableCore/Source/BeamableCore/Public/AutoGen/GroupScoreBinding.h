
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "GroupScoreBinding.generated.h"

UCLASS(BlueprintType)
class UGroupScoreBinding : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Board")
	FString Board;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Derivatives")
	TArray<FString> Derivatives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	int64 Score;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};