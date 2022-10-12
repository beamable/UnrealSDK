
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Enums/GroupType.h"

#include "GroupSearchRequestBody.generated.h"

UCLASS(BlueprintType)
class UGroupSearchRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FOptionalString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Min")
	FOptionalInt64 ScoreMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sort Field")
	FOptionalString SortField;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Score")
	FOptionalInt64 UserScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Slots")
	FOptionalBool bHasSlots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Types")
	FOptionalString EnrollmentTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset")
	FOptionalInt32 Offset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Max")
	FOptionalInt64 ScoreMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sub Group")
	FOptionalBool bSubGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sort Value")
	FOptionalInt32 SortValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type")
	EGroupType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};