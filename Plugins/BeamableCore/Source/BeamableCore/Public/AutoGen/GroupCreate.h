#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Enums/GroupType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "GroupCreate.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupCreate : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Type", Category="Beam")
	FString EnrollmentType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Requirement", Category="Beam")
	int64 Requirement = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EGroupType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Size", Category="Beam")
	int32 MaxSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag", Category="Beam")
	FOptionalString Tag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data", Category="Beam")
	FOptionalString ClientData = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time", Category="Beam")
	FOptionalInt32 Time = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group", Category="Beam")
	FOptionalInt64 Group = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scores", Category="Beam")
	FOptionalArrayOfGroupScoreBinding Scores = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};