
#include "BeamableCore/Public/AutoGen/ContentMeta.h"
#include "Serialization/BeamJsonUtils.h"




void UContentMeta::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeJsonObject(TEXT("data"), Data, Serializer);
	Serializer->WriteValue(TEXT("visibility"), UBeamJsonUtils::EnumToSerializationName(Visibility));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("text"), &Text, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("$link"), &link, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamContentId>, FBeamContentId, FString>(TEXT("$links"), &links, Serializer);
}

void UContentMeta::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeJsonObject(TEXT("data"), Data, Serializer);
	Serializer->WriteValue(TEXT("visibility"), UBeamJsonUtils::EnumToSerializationName(Visibility));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("text"), &Text, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("$link"), &link, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamContentId>, FBeamContentId, FString>(TEXT("$links"), &links, Serializer);		
}

void UContentMeta::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeJsonObject(TEXT("data"), Bag, Data, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("visibility")), Visibility);
	UBeamJsonUtils::DeserializeOptional<FString>("text", Bag, Text, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamContentId, FString>("$link", Bag, link, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamContentId>, FBeamContentId, FString>("$links", Bag, links, OuterOwner);
}



