
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Enums/GroupType.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "GroupCreate.generated.h"

UCLASS(BlueprintType)
class UGroupCreate : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Type")
	FString EnrollmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag")
	FOptionalString Tag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Requirement")
	int64 Requirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data")
	FOptionalString ClientData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scores")
	FOptionalArrayOfGroupScoreBinding Scores;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time")
	FOptionalInt32 Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type")
	EGroupType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Size")
	int32 MaxSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group")
	FOptionalInt64 Group;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};