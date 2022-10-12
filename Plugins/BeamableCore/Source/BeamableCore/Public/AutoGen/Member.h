
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"

#include "Member.generated.h"

UCLASS(BlueprintType)
class UMember : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Demote")
	FOptionalBool bCanDemote;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Kick")
	FOptionalBool bCanKick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role")
	FString Role;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag")
	int64 GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Promote")
	FOptionalBool bCanPromote;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scores")
	FOptionalArrayOfGroupScoreBinding Scores;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};