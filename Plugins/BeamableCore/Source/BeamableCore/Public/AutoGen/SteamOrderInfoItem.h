#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "SteamOrderInfoItem.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USteamOrderInfoItem : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Vat", Category="Beam")
	int64 Vat = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Amount", Category="Beam")
	int64 Amount = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Itemid", Category="Beam")
	int64 Itemid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Qty", Category="Beam")
	int64 Qty = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Itemstatus", Category="Beam")
	FString Itemstatus = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};