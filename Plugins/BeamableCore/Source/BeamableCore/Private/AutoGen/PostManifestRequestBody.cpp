
#include "BeamableCore/Public/AutoGen/PostManifestRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPostManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServiceReference*>(TEXT("manifest"), Manifest, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoDeploy"), &bAutoDeploy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);
}

void UPostManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServiceReference*>(TEXT("manifest"), Manifest, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoDeploy"), &bAutoDeploy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);		
}

void UPostManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UServiceReference*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("autoDeploy", Bag, bAutoDeploy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>("storageReferences", Bag, StorageReferences, OuterOwner);
}



