#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"

#include "DatabasePerformanceRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UDatabasePerformanceRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Object Name", Category="Beam")
	FString StorageObjectName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Granularity", Category="Beam")
	FString Granularity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Date", Category="Beam")
	FOptionalString EndDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date", Category="Beam")
	FOptionalString StartDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Period", Category="Beam")
	FOptionalString Period = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};