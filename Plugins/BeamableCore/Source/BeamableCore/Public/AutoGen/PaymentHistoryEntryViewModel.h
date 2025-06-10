#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "PaymentHistoryEntryViewModel.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UPaymentHistoryEntryViewModel : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Change", Category="Beam")
	FString Change = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Data", Category="Beam")
	FOptionalString Data = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Timestamp", Category="Beam")
	FOptionalString Timestamp = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};