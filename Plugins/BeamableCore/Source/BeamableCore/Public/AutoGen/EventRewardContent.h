
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfEventInventoryRewardCurrency.h"
#include "AutoGen/Optionals/OptionalArrayOfEventInventoryRewardItem.h"
#include "AutoGen/Optionals/OptionalDouble.h"
#include "AutoGen/Optionals/OptionalArrayOfEventRewardObtain.h"

#include "EventRewardContent.generated.h"

UCLASS(BlueprintType)
class UEventRewardContent : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies")
	FOptionalArrayOfEventInventoryRewardCurrency Currencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items")
	FOptionalArrayOfEventInventoryRewardItem Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Min")
	double Min;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max")
	FOptionalDouble Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain")
	FOptionalArrayOfEventRewardObtain Obtain;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};