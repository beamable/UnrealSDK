#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/TransactionDetails.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "BeginPaymentRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeginPaymentRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payment Provider", Category="Beam")
	FString PaymentProvider = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Details", Category="Beam")
	UTransactionDetails* Details = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Init History Data", Category="Beam")
	FOptionalString InitHistoryData = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};