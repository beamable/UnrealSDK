
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"

#include "EventInventoryPendingRewards.generated.h"

UCLASS(BlueprintType)
class UEventInventoryPendingRewards : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies")
	FOptionalMapOfString Currencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items")
	FOptionalArrayOfItemCreateRequestBody Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Empty")
	bool bEmpty;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};