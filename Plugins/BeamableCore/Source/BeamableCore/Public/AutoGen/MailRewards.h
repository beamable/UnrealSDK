#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/CurrencyChange.h"
#include "BeamableCore/Public/AutoGen/ItemCreateRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "MailRewards.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UMailRewards : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies", Category="Beam")
	TArray<UCurrencyChange*> Currencies = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items", Category="Beam")
	TArray<UItemCreateRequestBody*> Items = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Apply Vip Bonus", Category="Beam")
	FOptionalBool bApplyVipBonus = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};