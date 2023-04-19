
#include "BeamableCore/Public/AutoGen/BinaryReference.h"
#include "Serialization/BeamJsonUtils.h"




void UBinaryReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uploadMethod"), UploadMethod);
	Serializer->WriteValue(TEXT("uri"), Uri);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("uploadUri"), UploadUri);
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("visibility"), Visibility);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastChanged"), &LastChanged, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("created"), &Created, Serializer);
}

void UBinaryReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uploadMethod"), UploadMethod);
	Serializer->WriteValue(TEXT("uri"), Uri);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("uploadUri"), UploadUri);
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("visibility"), Visibility);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastChanged"), &LastChanged, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("created"), &Created, Serializer);		
}

void UBinaryReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UploadMethod = Bag->GetStringField(TEXT("uploadMethod"));
	Uri = Bag->GetStringField(TEXT("uri"));
	Version = Bag->GetStringField(TEXT("version"));
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	UploadUri = Bag->GetStringField(TEXT("uploadUri"));
	Type = Bag->GetStringField(TEXT("type"));
	Visibility = Bag->GetStringField(TEXT("visibility"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("tags")), Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("lastChanged", Bag, LastChanged, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("created", Bag, Created, OuterOwner);
}



