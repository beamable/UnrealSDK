
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "PaymentHistoryEntryViewModel.generated.h"

UCLASS(BlueprintType)
class UPaymentHistoryEntryViewModel : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Change")
	FString Change;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Data")
	FOptionalString Data;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Timestamp")
	FOptionalString Timestamp;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};