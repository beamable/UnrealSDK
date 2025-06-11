#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"

#include "Member.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UMember : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role", Category="Beam")
	FString Role = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	int64 GamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Demote", Category="Beam")
	FOptionalBool bCanDemote = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Kick", Category="Beam")
	FOptionalBool bCanKick = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Promote", Category="Beam")
	FOptionalBool bCanPromote = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scores", Category="Beam")
	FOptionalArrayOfGroupScoreBinding Scores = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};