
#include "BeamableCore/Public/AutoGen/ContentMeta.h"
#include "Serialization/BeamJsonUtils.h"




void UContentMeta::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeJsonObject(TEXT("data"), Data, Serializer);
	Serializer->WriteValue(TEXT("visibility"), UContentVisibilityLibrary::ContentVisibilityToSerializationName(Visibility));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("text"), &Text, Serializer);
}

void UContentMeta::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeJsonObject(TEXT("data"), Data, Serializer);
	Serializer->WriteValue(TEXT("visibility"), UContentVisibilityLibrary::ContentVisibilityToSerializationName(Visibility));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("text"), &Text, Serializer);		
}

void UContentMeta::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeJsonObject(TEXT("data"), Bag, Data, OuterOwner);
	Visibility = UContentVisibilityLibrary::SerializationNameToContentVisibility(Bag->GetStringField(TEXT("visibility")));
	UBeamJsonUtils::DeserializeOptional<FString>("text", Bag, Text, OuterOwner);
}



