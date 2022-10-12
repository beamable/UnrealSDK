
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/CurrencyView.h"
#include "AutoGen/ItemGroup.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "InventoryView.generated.h"

UCLASS(BlueprintType)
class UInventoryView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies")
	TArray<UCurrencyView*> Currencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items")
	TArray<UItemGroup*> Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope")
	FOptionalString Scope;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};