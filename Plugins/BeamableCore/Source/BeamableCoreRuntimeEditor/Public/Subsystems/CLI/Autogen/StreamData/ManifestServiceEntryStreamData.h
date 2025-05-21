
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/UnityAssemblyReferenceDataStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/FederationEntryStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ManifestServiceEntryStreamData.generated.h"


UCLASS(BlueprintType)
class UManifestServiceEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BeamoId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldBeEnabledOnRemote = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CsprojPath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BuildDllPath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> StorageDependencies = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UUnityAssemblyReferenceDataStreamData*> UnityReferences = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UFederationEntryStreamData*> Federations = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("beamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("shouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("csprojPath"), CsprojPath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("buildDllPath"), BuildDllPath, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("storageDependencies"), StorageDependencies, Serializer);
		UBeamJsonUtils::SerializeArray<UUnityAssemblyReferenceDataStreamData*>(TEXT("unityReferences"), UnityReferences, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationEntryStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("beamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("shouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("csprojPath"), CsprojPath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("buildDllPath"), BuildDllPath, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("storageDependencies"), StorageDependencies, Serializer);
		UBeamJsonUtils::SerializeArray<UUnityAssemblyReferenceDataStreamData*>(TEXT("unityReferences"), UnityReferences, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationEntryStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("beamoId")), BeamoId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("shouldBeEnabledOnRemote")), ShouldBeEnabledOnRemote);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("csprojPath")), CsprojPath);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("buildDllPath")), BuildDllPath);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("storageDependencies")), StorageDependencies, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UUnityAssemblyReferenceDataStreamData*>(Bag->GetArrayField(TEXT("unityReferences")), UnityReferences, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UFederationEntryStreamData*>(Bag->GetArrayField(TEXT("federations")), Federations, OuterOwner);	
	}
};


