
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"
#include "AutoGen/Optionals/OptionalCommerceLootRoll.h"
#include "AutoGen/Optionals/OptionalArrayOfCurrencyChange.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "OfferDefinition.generated.h"

UCLASS(BlueprintType)
class UOfferDefinition : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Titles")
	TArray<FString> Titles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Items")
	FOptionalArrayOfItemCreateRequestBody ObtainItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Loot Roll")
	FOptionalCommerceLootRoll LootRoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Currency")
	FOptionalArrayOfCurrencyChange ObtainCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Metadata")
	FOptionalString Metadata;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Images")
	TArray<FString> Images;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Descriptions")
	TArray<FString> Descriptions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain")
	TArray<FString> Obtain;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};