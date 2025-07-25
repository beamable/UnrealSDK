
#include "BeamableCore/Public/AutoGen/BeamoV2Manifest.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2Manifest::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2Manifest::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdByAccountId"), &CreatedByAccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageGroupId"), &StorageGroupId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceReference*>, UBeamoV2ServiceReference*>(TEXT("serviceReferences"), &ServiceReferences, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceStorageReference*>, UBeamoV2ServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);
}

void UBeamoV2Manifest::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdByAccountId"), &CreatedByAccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageGroupId"), &StorageGroupId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceReference*>, UBeamoV2ServiceReference*>(TEXT("serviceReferences"), &ServiceReferences, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceStorageReference*>, UBeamoV2ServiceStorageReference*>(TEXT("storageReferences"), &StorageReferences, Serializer);		
}

void UBeamoV2Manifest::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdByAccountId", Bag, CreatedByAccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("storageGroupId", Bag, StorageGroupId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceReference*>, UBeamoV2ServiceReference*>("serviceReferences", Bag, ServiceReferences, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceStorageReference*>, UBeamoV2ServiceStorageReference*>("storageReferences", Bag, StorageReferences, OuterOwner);
}



