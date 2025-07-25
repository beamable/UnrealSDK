
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("archived")), bArchived);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("enabled")), bEnabled);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("storageType")), StorageType);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("checksum")), Checksum);
	UBeamJsonUtils::DeserializeOptional<FString>("templateId", Bag, TemplateId, OuterOwner);
}



