
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "PaymentDetailsEntryViewModel.generated.h"

UCLASS(BlueprintType)
class UPaymentDetailsEntryViewModel : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Reference")
	FString Reference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Quantity")
	int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku")
	FString Sku;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price")
	int32 Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subcategory")
	FOptionalString Subcategory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gameplace")
	FString Gameplace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Local Price")
	FOptionalString LocalPrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category")
	FOptionalString Category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Local Currency")
	FOptionalString LocalCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Product Id")
	FString ProviderProductId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};