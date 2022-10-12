
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "LocalizationRef.generated.h"

UCLASS(BlueprintType)
class ULocalizationRef : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Localization Id")
	FString LocalizationId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Default Value")
	FOptionalString DefaultValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Empty")
	bool bEmpty;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};