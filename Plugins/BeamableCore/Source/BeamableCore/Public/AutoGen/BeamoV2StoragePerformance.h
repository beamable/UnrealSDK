#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/BeamoV2PANamespace.h"
#include "BeamableCore/Public/AutoGen/BeamoV2PASuggestedIndex.h"
#include "BeamableCore/Public/AutoGen/BeamoV2PASlowQuery.h"
#include "BeamableCore/Public/AutoGen/BeamoV2DatabaseMeasurements.h"

#include "BeamoV2StoragePerformance.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2StoragePerformance : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Database Measurements", Category="Beam")
	UBeamoV2DatabaseMeasurements* DatabaseMeasurements = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Namespaces", Category="Beam")
	TArray<UBeamoV2PANamespace*> Namespaces = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Indexes", Category="Beam")
	TArray<UBeamoV2PASuggestedIndex*> Indexes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Queries", Category="Beam")
	TArray<UBeamoV2PASlowQuery*> Queries = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};