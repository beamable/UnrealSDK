
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalMapOfInt64.h"

#include "TransferRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTransferRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Recipient Player", Category="Beam")
	int64 RecipientPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction", Category="Beam")
	FOptionalString Transaction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies", Category="Beam")
	FOptionalMapOfInt64 Currencies;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};