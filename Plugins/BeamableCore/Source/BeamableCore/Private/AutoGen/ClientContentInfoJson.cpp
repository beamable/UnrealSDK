
#include "BeamableCore/Public/AutoGen/ClientContentInfoJson.h"
#include "Serialization/BeamJsonUtils.h"




void UClientContentInfoJson::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uri"), Uri);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
	Serializer->WriteValue(TEXT("type"), UContentTypeLibrary::ContentTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
}

void UClientContentInfoJson::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uri"), Uri);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
	Serializer->WriteValue(TEXT("type"), UContentTypeLibrary::ContentTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);		
}

void UClientContentInfoJson::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Uri = Bag->GetStringField(TEXT("uri"));
	Version = Bag->GetStringField(TEXT("version"));
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("contentId")), ContentId, OuterOwner);
	Type = UContentTypeLibrary::SerializationNameToContentType(Bag->GetStringField(TEXT("type")));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("tags")), Tags, OuterOwner);
}



