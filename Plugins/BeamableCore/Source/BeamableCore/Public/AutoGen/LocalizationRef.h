#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "LocalizationRef.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API ULocalizationRef : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Empty", Category="Beam")
	bool bEmpty = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Localization Id", Category="Beam")
	FString LocalizationId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Default Value", Category="Beam")
	FOptionalString DefaultValue = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};