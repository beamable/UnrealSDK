
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStorageReference.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceStorageReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("enabled"), &bEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageType"), &StorageType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("templateId"), &TemplateId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
}

void UBeamoV2ServiceStorageReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("enabled"), &bEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageType"), &StorageType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("templateId"), &TemplateId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);		
}

void UBeamoV2ServiceStorageReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("enabled", Bag, bEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("storageType", Bag, StorageType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("templateId", Bag, TemplateId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
}



