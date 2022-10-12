
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"
#include "AutoGen/GroupUserMember.h"
#include "AutoGen/Arrays/ArrayOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"

#include "GroupUser.generated.h"

UCLASS(BlueprintType)
class UGroupUser : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight")
	FOptionalArrayOfInFlightMessage InFlight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag")
	int64 GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="All Groups")
	TArray<UGroupUserMember*> AllGroups;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated")
	int64 Updated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Member")
	TMap<FString, FArrayOfString> Member;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scores")
	FOptionalArrayOfGroupScoreBinding Scores;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};