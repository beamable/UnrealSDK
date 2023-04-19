
#include "BeamableCore/Public/AutoGen/ServiceStorageReference.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceStorageReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("archived"), bArchived);
	Serializer->WriteValue(TEXT("enabled"), bEnabled);
	Serializer->WriteValue(TEXT("storageType"), StorageType);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("templateId"), &TemplateId, Serializer);
}

void UServiceStorageReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("archived"), bArchived);
	Serializer->WriteValue(TEXT("enabled"), bEnabled);
	Serializer->WriteValue(TEXT("storageType"), StorageType);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("templateId"), &TemplateId, Serializer);		
}

void UServiceStorageReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bArchived = Bag->GetBoolField(TEXT("archived"));
	bEnabled = Bag->GetBoolField(TEXT("enabled"));
	StorageType = Bag->GetStringField(TEXT("storageType"));
	Id = Bag->GetStringField(TEXT("id"));
	Checksum = Bag->GetStringField(TEXT("checksum"));
	UBeamJsonUtils::DeserializeOptional<FString>("templateId", Bag, TemplateId, OuterOwner);
}



