#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "TransactionDetails.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UTransactionDetails : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price Cents", Category="Beam")
	int32 PriceCents = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku", Category="Beam")
	FString Sku = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Product Id", Category="Beam")
	FString ProviderProductId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Quantity", Category="Beam")
	FOptionalInt32 Quantity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FOptionalString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Reference", Category="Beam")
	FOptionalString Reference = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Place", Category="Beam")
	FOptionalString GamePlace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category", Category="Beam")
	FOptionalString Category = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subcategory", Category="Beam")
	FOptionalString Subcategory = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Local Currency", Category="Beam")
	FOptionalString LocalCurrency = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Local Price", Category="Beam")
	FOptionalString LocalPrice = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};