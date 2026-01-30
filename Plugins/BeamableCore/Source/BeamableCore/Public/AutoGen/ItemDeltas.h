#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/ItemPropertiesDelta.h"

#include "ItemDeltas.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UItemDeltas : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	TArray<UItemPropertiesDelta*> Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated", Category="Beam")
	TArray<UItemPropertiesDelta*> Updated = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Deleted", Category="Beam")
	TArray<UItemPropertiesDelta*> Deleted = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};