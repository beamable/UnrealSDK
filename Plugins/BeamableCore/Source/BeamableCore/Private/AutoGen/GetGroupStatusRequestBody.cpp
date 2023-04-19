
#include "BeamableCore/Public/AutoGen/GetGroupStatusRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetGroupStatusRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
}

void UGetGroupStatusRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);		
}

void UGetGroupStatusRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("contentId", Bag, ContentId, OuterOwner);
}



