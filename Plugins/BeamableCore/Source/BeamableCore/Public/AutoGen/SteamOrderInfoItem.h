
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "SteamOrderInfoItem.generated.h"

UCLASS(BlueprintType)
class USteamOrderInfoItem : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Vat")
	int64 Vat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Amount")
	int64 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Itemid")
	int64 Itemid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Qty")
	int64 Qty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Itemstatus")
	FString Itemstatus;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};