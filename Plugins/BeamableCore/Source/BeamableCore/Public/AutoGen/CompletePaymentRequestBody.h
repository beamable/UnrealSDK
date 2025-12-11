#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "CompletePaymentRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCompletePaymentRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payment Provider", Category="Beam")
	FString PaymentProvider = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Receipt", Category="Beam")
	FString Receipt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};