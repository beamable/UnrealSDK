#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "LocalizedPrice.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API ULocalizedPrice : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To", Category="Beam")
	int64 To = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price", Category="Beam")
	int64 Price = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price Localized", Category="Beam")
	double PriceLocalized = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price Localized String", Category="Beam")
	FString PriceLocalizedString = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};