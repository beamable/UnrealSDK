
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalMapOfInt64.h"

#include "TransferRequestBody.generated.h"

UCLASS(BlueprintType)
class UTransferRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction")
	FOptionalString Transaction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Recipient Player")
	int64 RecipientPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies")
	FOptionalMapOfInt64 Currencies;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};