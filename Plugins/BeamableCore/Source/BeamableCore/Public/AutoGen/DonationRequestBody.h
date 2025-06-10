#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/DonationEntry.h"
#include "BeamableCore/Public/AutoGen/Currency.h"

#include "DonationRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UDonationRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Satisfied", Category="Beam")
	bool bSatisfied = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time Requested", Category="Beam")
	int64 TimeRequested = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	int64 PlayerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency", Category="Beam")
	UCurrency* Currency = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Progress", Category="Beam")
	TArray<UDonationEntry*> Progress = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};