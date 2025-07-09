
#include "BeamableCore/Public/AutoGen/PostManifestRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPostManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoDeploy"), &bAutoDeploy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoActorServiceReference*>, UBeamoActorServiceReference*>(TEXT("manifest"), &Manifest, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);
}

void UPostManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoDeploy"), &bAutoDeploy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoActorServiceReference*>, UBeamoActorServiceReference*>(TEXT("manifest"), &Manifest, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);		
}

void UPostManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("autoDeploy", Bag, bAutoDeploy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoActorServiceReference*>, UBeamoActorServiceReference*>("manifest", Bag, Manifest, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>("storageReferences", Bag, StorageReferences, OuterOwner);
}



