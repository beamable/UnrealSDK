
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
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("beamoId")), BeamoId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("csprojPath")), CsprojPath);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("shouldBeEnabledOnRemote")), ShouldBeEnabledOnRemote);
		UBeamJsonUtils::DeserializeArray<UUnityAssemblyReferenceDataStreamData*>(Bag->GetArrayField(TEXT("unityReferences")), UnityReferences, OuterOwner);	
	}
};


