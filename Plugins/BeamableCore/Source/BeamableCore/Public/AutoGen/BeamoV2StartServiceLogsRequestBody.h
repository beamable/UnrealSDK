#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2OrderDirection.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"

#include "BeamoV2StartServiceLogsRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2StartServiceLogsRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FOptionalString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time", Category="Beam")
	FOptionalDateTime StartTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time", Category="Beam")
	FOptionalDateTime EndTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Order", Category="Beam")
	FOptionalBeamoV2OrderDirection Order = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Filters", Category="Beam")
	FOptionalArrayOfString Filters = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};