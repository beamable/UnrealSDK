#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "ProductView.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UProductView : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Localized Price", Category="Beam")
	double LocalizedPrice = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku", Category="Beam")
	FString Sku = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description", Category="Beam")
	FString Description = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Iso Currency Code", Category="Beam")
	FString IsoCurrencyCode = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Localized Price String", Category="Beam")
	FString LocalizedPriceString = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};