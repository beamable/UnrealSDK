
#include "BeamableCore/Public/AutoGen/BeamoActorManifest.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoActorManifest::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoActorManifest::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdByAccountId"), &CreatedByAccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageGroupId"), &StorageGroupId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoActorServiceReference*>, UBeamoActorServiceReference*>(TEXT("serviceReferences"), &ServiceReferences, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);
}

void UBeamoActorManifest::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdByAccountId"), &CreatedByAccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageGroupId"), &StorageGroupId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoActorServiceReference*>, UBeamoActorServiceReference*>(TEXT("serviceReferences"), &ServiceReferences, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);		
}

void UBeamoActorManifest::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdByAccountId", Bag, CreatedByAccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("storageGroupId", Bag, StorageGroupId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoActorServiceReference*>, UBeamoActorServiceReference*>("serviceReferences", Bag, ServiceReferences, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>("storageReferences", Bag, StorageReferences, OuterOwner);
}



