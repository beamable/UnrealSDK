
#include "BeamableCore/Public/AutoGen/ObjectMetadataResponse.h"
#include "Serialization/BeamJsonUtils.h"




void UObjectMetadataResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("metadata"), Metadata, Serializer);
}

void UObjectMetadataResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("metadata"), Metadata, Serializer);		
}

void UObjectMetadataResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("objectKey"), Bag, ObjectKey);
	UBeamJsonUtils::DeserializeMap<FString>(TEXT("metadata"), Bag, Metadata, OuterOwner);
}



