#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "RegisterGroundItemRequestArgs.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API URegisterGroundItemRequestArgs : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Ground Item Id", Category="Beam")
	FString GroundItemId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FString ContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Quantity", Category="Beam")
	int32 Quantity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Item Type", Category="Beam")
	FString ItemType = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};