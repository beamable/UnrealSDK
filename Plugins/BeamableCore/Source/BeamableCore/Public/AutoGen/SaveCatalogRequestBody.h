
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Store.h"
#include "AutoGen/OfferDefinition.h"

#include "SaveCatalogRequestBody.generated.h"

UCLASS(BlueprintType)
class USaveCatalogRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stores")
	TArray<UStore*> Stores;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offer Definitions")
	TArray<UOfferDefinition*> OfferDefinitions;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};