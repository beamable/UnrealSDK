#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfScheduleDefinition.h"

#include "Schedule.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USchedule : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active From", Category="Beam")
	FString ActiveFrom = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description", Category="Beam")
	FOptionalString Description = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active To", Category="Beam")
	FOptionalString ActiveTo = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Crons", Category="Beam")
	FOptionalArrayOfString Crons = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Definitions", Category="Beam")
	FOptionalArrayOfScheduleDefinition Definitions = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};