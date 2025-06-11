#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamCid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamPid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "UpdateRole.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UUpdateRole : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	FOptionalBeamCid Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm", Category="Beam")
	FOptionalBeamPid Realm = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role", Category="Beam")
	FOptionalString Role = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};