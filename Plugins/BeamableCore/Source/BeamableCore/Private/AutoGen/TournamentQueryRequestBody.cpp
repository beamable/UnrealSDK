
#include "BeamableCore/Public/AutoGen/TournamentQueryRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UTournamentQueryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isRunning"), &bIsRunning, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cycle"), &Cycle, Serializer);
}

void UTournamentQueryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isRunning"), &bIsRunning, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cycle"), &Cycle, Serializer);		
}

void UTournamentQueryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("isRunning", Bag, bIsRunning, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("contentId", Bag, ContentId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("cycle", Bag, Cycle, OuterOwner);
}



