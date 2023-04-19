
#include "BeamableCore/Public/AutoGen/ContentMeta.h"
#include "Serialization/BeamJsonUtils.h"




void UContentMeta::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("visibility"), UContentVisibilityLibrary::ContentVisibilityToSerializationName(Visibility));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("text"), &Text, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("data"), &Data, Serializer);
}

void UContentMeta::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("visibility"), UContentVisibilityLibrary::ContentVisibilityToSerializationName(Visibility));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("text"), &Text, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("data"), &Data, Serializer);		
}

void UContentMeta::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Visibility = UContentVisibilityLibrary::SerializationNameToContentVisibility(Bag->GetStringField(TEXT("visibility")));
	UBeamJsonUtils::DeserializeOptional<FString>("text", Bag, Text, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("data", Bag, Data, OuterOwner);
}



