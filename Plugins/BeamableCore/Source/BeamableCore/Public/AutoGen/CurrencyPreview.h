
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "CurrencyPreview.generated.h"

UCLASS(BlueprintType)
class UCurrencyPreview : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Amount")
	int64 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Original Amount")
	int64 OriginalAmount;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};