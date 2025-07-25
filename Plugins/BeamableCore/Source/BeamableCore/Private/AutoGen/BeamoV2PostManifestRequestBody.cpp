
#include "BeamableCore/Public/AutoGen/BeamoV2PostManifestRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2PostManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoDeploy"), &bAutoDeploy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceReference*>, UBeamoV2ServiceReference*>(TEXT("manifest"), &Manifest, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceStorageReference*>, UBeamoV2ServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);
}

void UBeamoV2PostManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoDeploy"), &bAutoDeploy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceReference*>, UBeamoV2ServiceReference*>(TEXT("manifest"), &Manifest, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceStorageReference*>, UBeamoV2ServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);		
}

void UBeamoV2PostManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("autoDeploy", Bag, bAutoDeploy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceReference*>, UBeamoV2ServiceReference*>("manifest", Bag, Manifest, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceStorageReference*>, UBeamoV2ServiceStorageReference*>("storageReferences", Bag, StorageReferences, OuterOwner);
}



