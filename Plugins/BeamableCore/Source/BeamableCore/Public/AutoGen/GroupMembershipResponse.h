
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Enums/GroupType.h"
#include "AutoGen/GroupMetaData.h"

#include "GroupMembershipResponse.generated.h"

UCLASS(BlueprintType)
class UGroupMembershipResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag")
	FOptionalInt64 GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Member")
	bool bMember;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type")
	EGroupType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sub Groups")
	TArray<int64> SubGroups;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group")
	UGroupMetaData* Group;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};