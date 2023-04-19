
#include "BeamableCore/Public/AutoGen/GetContentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetContentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
	Serializer->WriteValue(TEXT("version"), Version);
}

void UGetContentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
	Serializer->WriteValue(TEXT("version"), Version);		
}

void UGetContentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("contentId")), ContentId, OuterOwner);
	Version = Bag->GetStringField(TEXT("version"));
}



