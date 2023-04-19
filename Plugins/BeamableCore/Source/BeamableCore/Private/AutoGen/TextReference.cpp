
#include "BeamableCore/Public/AutoGen/TextReference.h"
#include "Serialization/BeamJsonUtils.h"




void UTextReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uri"), Uri);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("visibility"), Visibility);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastChanged"), &LastChanged, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void UTextReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uri"), Uri);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("visibility"), Visibility);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastChanged"), &LastChanged, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void UTextReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Uri = Bag->GetStringField(TEXT("uri"));
	Version = Bag->GetStringField(TEXT("version"));
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	Type = Bag->GetStringField(TEXT("type"));
	Visibility = Bag->GetStringField(TEXT("visibility"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("tags")), Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("lastChanged", Bag, LastChanged, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}



