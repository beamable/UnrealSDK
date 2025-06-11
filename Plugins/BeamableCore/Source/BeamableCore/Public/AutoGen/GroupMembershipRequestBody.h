#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamGroupType.h"
#include "Serialization/BeamJsonUtils.h"

#include "GroupMembershipRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGroupMembershipRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EBeamGroupType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group", Category="Beam")
	int64 Group = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Successor", Category="Beam")
	FOptionalInt64 Successor = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score", Category="Beam")
	FOptionalInt64 Score = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sub Group", Category="Beam")
	FOptionalInt64 SubGroup = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};