
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/UnityAssemblyReferenceDataStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ManifestStorageEntryStreamData.generated.h"


UCLASS(BlueprintType)
class UManifestStorageEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BeamoId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CsprojPath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldBeEnabledOnRemote = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UUnityAssemblyReferenceDataStreamData*> UnityReferences = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("beamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("csprojPath"), CsprojPath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("shouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote, Serializer);
		UBeamJsonUtils::SerializeArray<UUnityAssemblyReferenceDataStreamData*>(TEXT("unityReferences"), UnityReferences, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("beamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("csprojPath"), CsprojPath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("shouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote, Serializer);
		UBeamJsonUtils::SerializeArray<UUnityAssemblyReferenceDataStreamData*>(TEXT("unityReferences"), UnityReferences, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("beamoId"), Bag, BeamoId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("csprojPath"), Bag, CsprojPath);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("shouldBeEnabledOnRemote"), Bag, ShouldBeEnabledOnRemote);
		UBeamJsonUtils::DeserializeArray<UUnityAssemblyReferenceDataStreamData*>(TEXT("unityReferences"), Bag, UnityReferences, OuterOwner);	
	}
};


