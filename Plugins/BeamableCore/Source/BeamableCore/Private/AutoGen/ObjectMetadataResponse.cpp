
#include "BeamableCore/Public/AutoGen/ObjectMetadataResponse.h"
#include "Serialization/BeamJsonUtils.h"




void UObjectMetadataResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("metadata"), Metadata, Serializer);
}

void UObjectMetadataResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("metadata"), Metadata, Serializer);		
}

void UObjectMetadataResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ObjectKey = Bag->GetStringField(TEXT("objectKey"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("metadata")), Metadata, OuterOwner);
}



