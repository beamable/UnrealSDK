
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"
#include "AutoGen/GroupUserMember.h"
#include "AutoGen/Arrays/ArrayOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"

#include "GroupUser.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupUser : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	int64 GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated", Category="Beam")
	int64 Updated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="All Groups", Category="Beam")
	TArray<UGroupUserMember*> AllGroups;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Member", Category="Beam")
	TMap<FString, FArrayOfString> Member;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight", Category="Beam")
	FOptionalArrayOfInFlightMessage InFlight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scores", Category="Beam")
	FOptionalArrayOfGroupScoreBinding Scores;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};