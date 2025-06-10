#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "PaymentDetailsEntryViewModel.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UPaymentDetailsEntryViewModel : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Reference", Category="Beam")
	FString Reference = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Quantity", Category="Beam")
	int32 Quantity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku", Category="Beam")
	FString Sku = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price", Category="Beam")
	int32 Price = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gameplace", Category="Beam")
	FString Gameplace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Product Id", Category="Beam")
	FString ProviderProductId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subcategory", Category="Beam")
	FOptionalString Subcategory = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Local Price", Category="Beam")
	FOptionalString LocalPrice = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category", Category="Beam")
	FOptionalString Category = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Local Currency", Category="Beam")
	FOptionalString LocalCurrency = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};