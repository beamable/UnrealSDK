
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "MakeDonationRequestBody.generated.h"

UCLASS(BlueprintType)
class UMakeDonationRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Recipient Id")
	int64 RecipientId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Amount")
	int64 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Auto Claim")
	FOptionalBool bAutoClaim;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};