
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/CurrencyChange.h"
#include "AutoGen/ItemCreateRequestBody.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "MailRewards.generated.h"

UCLASS(BlueprintType)
class UMailRewards : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies")
	TArray<UCurrencyChange*> Currencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items")
	TArray<UItemCreateRequestBody*> Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Apply Vip Bonus")
	FOptionalBool bApplyVipBonus;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};