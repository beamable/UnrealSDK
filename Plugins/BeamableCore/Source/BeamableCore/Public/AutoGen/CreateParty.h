#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"

#include "CreateParty.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCreateParty : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Restriction", Category="Beam")
	FOptionalString Restriction = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leader", Category="Beam")
	FOptionalBeamGamerTag Leader = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Size", Category="Beam")
	FOptionalInt32 MaxSize = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};