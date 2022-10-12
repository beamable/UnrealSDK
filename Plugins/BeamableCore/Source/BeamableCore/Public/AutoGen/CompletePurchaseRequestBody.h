
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "CompletePurchaseRequestBody.generated.h"

UCLASS(BlueprintType)
class UCompletePurchaseRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Txid")
	int64 Txid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Receipt")
	FString Receipt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price In Local Currency")
	FString PriceInLocalCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Iso Currency Symbol")
	FString IsoCurrencySymbol;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};