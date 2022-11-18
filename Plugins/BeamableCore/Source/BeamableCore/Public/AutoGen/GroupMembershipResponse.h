
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Enums/GroupType.h"
#include "AutoGen/GroupMetaData.h"

#include "GroupMembershipResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupMembershipResponse : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Member", Category="Beam")
	bool bMember;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EGroupType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group", Category="Beam")
	UGroupMetaData* Group;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sub Groups", Category="Beam")
	TArray<int64> SubGroups;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	FOptionalInt64 GamerTag;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};