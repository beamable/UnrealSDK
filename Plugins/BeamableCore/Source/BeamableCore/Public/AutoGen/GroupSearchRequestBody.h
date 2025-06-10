#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamGroupType.h"

#include "GroupSearchRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGroupSearchRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EBeamGroupType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Slots", Category="Beam")
	FOptionalBool bHasSlots = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sub Group", Category="Beam")
	FOptionalBool bSubGroup = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FOptionalString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Min", Category="Beam")
	FOptionalInt64 ScoreMin = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sort Field", Category="Beam")
	FOptionalString SortField = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Score", Category="Beam")
	FOptionalInt64 UserScore = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Types", Category="Beam")
	FOptionalString EnrollmentTypes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset", Category="Beam")
	FOptionalInt32 Offset = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Max", Category="Beam")
	FOptionalInt64 ScoreMax = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sort Value", Category="Beam")
	FOptionalInt32 SortValue = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};