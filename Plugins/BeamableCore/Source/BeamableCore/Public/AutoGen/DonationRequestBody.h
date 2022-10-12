
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/DonationEntry.h"
#include "AutoGen/Currency.h"

#include "DonationRequestBody.generated.h"

UCLASS(BlueprintType)
class UDonationRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time Requested")
	int64 TimeRequested;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Progress")
	TArray<UDonationEntry*> Progress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Satisfied")
	bool bSatisfied;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	int64 PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency")
	UCurrency* Currency;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};