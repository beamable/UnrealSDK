
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/PlayerListingView.h"

#include "ActiveListingResponse.generated.h"

UCLASS(BlueprintType)
class UActiveListingResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Store Symbol")
	FString StoreSymbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Listing")
	UPlayerListingView* Listing;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};