
#include "BeamableCore/Public/AutoGen/GetContentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetContentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
}

void UGetContentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);		
}

void UGetContentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("contentId"), Bag, ContentId, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("version"), Bag, Version);
}



