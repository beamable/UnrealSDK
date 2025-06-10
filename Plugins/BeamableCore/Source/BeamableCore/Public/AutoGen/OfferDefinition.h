#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalCommerceLootRoll.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCurrencyChange.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "OfferDefinition.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UOfferDefinition : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Titles", Category="Beam")
	TArray<FString> Titles = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Images", Category="Beam")
	TArray<FString> Images = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Descriptions", Category="Beam")
	TArray<FString> Descriptions = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain", Category="Beam")
	TArray<FString> Obtain = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Loot Roll", Category="Beam")
	FOptionalCommerceLootRoll LootRoll = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Metadata", Category="Beam")
	FOptionalString Metadata = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Items", Category="Beam")
	FOptionalArrayOfItemCreateRequestBody ObtainItems = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Currency", Category="Beam")
	FOptionalArrayOfCurrencyChange ObtainCurrency = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};