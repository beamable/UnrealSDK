
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/OfferConstraint.h"

#include "OfferRequirement.generated.h"

UCLASS(BlueprintType)
class UOfferRequirement : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offer Symbol")
	FString OfferSymbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Purchases")
	UOfferConstraint* Purchases;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};