
#include "BeamableCore/Public/AutoGen/ServiceStorageReference.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceStorageReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("archived"), bArchived, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), bEnabled, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("templateId"), &TemplateId, Serializer);
}

void UServiceStorageReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("archived"), bArchived, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), bEnabled, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("templateId"), &TemplateId, Serializer);		
}

void UServiceStorageReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("archived"), Bag, bArchived);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("enabled"), Bag, bEnabled);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("storageType"), Bag, StorageType);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);
	UBeamJsonUtils::DeserializeOptional<FString>("templateId", Bag, TemplateId, OuterOwner);
}



