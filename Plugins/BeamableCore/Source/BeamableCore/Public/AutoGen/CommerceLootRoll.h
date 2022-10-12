
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"

#include "CommerceLootRoll.generated.h"

UCLASS(BlueprintType)
class UCommerceLootRoll : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Preroll")
	bool bPreroll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External Tables")
	FOptionalArrayOfString ExternalTables;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};