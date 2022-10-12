
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/LocalizedPrice.h"

#include "LocalizedPriceMap.generated.h"

UCLASS(BlueprintType)
class ULocalizedPriceMap : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency")
	FString Currency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Prices")
	TArray<ULocalizedPrice*> Prices;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};