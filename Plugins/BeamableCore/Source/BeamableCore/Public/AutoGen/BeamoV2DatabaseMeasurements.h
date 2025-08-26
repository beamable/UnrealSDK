#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2Link.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2DatabaseMeasurement.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"

#include "BeamoV2DatabaseMeasurements.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2DatabaseMeasurements : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Database Name", Category="Beam")
	FString DatabaseName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Granularity", Category="Beam")
	FOptionalString Granularity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Id", Category="Beam")
	FOptionalString GroupId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Host Id", Category="Beam")
	FOptionalString HostId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Process Id", Category="Beam")
	FOptionalString ProcessId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start", Category="Beam")
	FOptionalDateTime Start = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End", Category="Beam")
	FOptionalDateTime End = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Links", Category="Beam")
	FOptionalArrayOfBeamoV2Link Links = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Measurements", Category="Beam")
	FOptionalArrayOfBeamoV2DatabaseMeasurement Measurements = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};