
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfScheduleDefinition.h"

#include "Schedule.generated.h"

UCLASS(BlueprintType)
class USchedule : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description")
	FOptionalString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Crons")
	FOptionalArrayOfString Crons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active To")
	FOptionalString ActiveTo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active From")
	FString ActiveFrom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Definitions")
	FOptionalArrayOfScheduleDefinition Definitions;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};