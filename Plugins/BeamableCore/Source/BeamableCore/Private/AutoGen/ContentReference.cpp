
#include "BeamableCore/Public/AutoGen/ContentReference.h"
#include "Serialization/BeamJsonUtils.h"




void UContentReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tag"), Tag);
	Serializer->WriteValue(TEXT("uri"), Uri);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("visibility"), UContentVisibilityLibrary::ContentVisibilityToSerializationName(Visibility));
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastChanged"), &LastChanged, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void UContentReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tag"), Tag);
	Serializer->WriteValue(TEXT("uri"), Uri);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("visibility"), UContentVisibilityLibrary::ContentVisibilityToSerializationName(Visibility));
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastChanged"), &LastChanged, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void UContentReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Tag = Bag->GetStringField(TEXT("tag"));
	Uri = Bag->GetStringField(TEXT("uri"));
	Version = Bag->GetStringField(TEXT("version"));
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	Type = Bag->GetStringField(TEXT("type"));
	Visibility = UContentVisibilityLibrary::SerializationNameToContentVisibility(Bag->GetStringField(TEXT("visibility")));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("tags")), Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("lastChanged", Bag, LastChanged, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}



