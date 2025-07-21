#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "BeamoV2ProtoError.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2ProtoError : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Status", Category="Beam")
	FOptionalInt32 Status = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Error", Category="Beam")
	FOptionalString Error = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description", Category="Beam")
	FOptionalString Description = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};