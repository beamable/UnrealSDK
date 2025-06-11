#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfDatabaseMeasurement.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Link.h"
#include "Serialization/BeamJsonUtils.h"

#include "DatabaseMeasurements.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UDatabaseMeasurements : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Database Name", Category="Beam")
	FString DatabaseName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Links", Category="Beam")
	TArray<ULink*> Links = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Id", Category="Beam")
	FOptionalString GroupId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Host Id", Category="Beam")
	FOptionalString HostId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Granularity", Category="Beam")
	FOptionalString Granularity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End", Category="Beam")
	FOptionalString End = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start", Category="Beam")
	FOptionalString Start = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Process Id", Category="Beam")
	FOptionalString ProcessId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Measurements", Category="Beam")
	FOptionalArrayOfDatabaseMeasurement Measurements = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};