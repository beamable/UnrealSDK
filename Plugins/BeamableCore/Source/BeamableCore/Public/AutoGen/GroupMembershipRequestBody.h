
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Enums/GroupType.h"

#include "GroupMembershipRequestBody.generated.h"

UCLASS(BlueprintType)
class UGroupMembershipRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Successor")
	FOptionalInt64 Successor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	FOptionalInt64 Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sub Group")
	FOptionalInt64 SubGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type")
	EGroupType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group")
	int64 Group;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};