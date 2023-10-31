
#include "BeamableCore/Public/AutoGen/OnlineStatusResponses.h"
#include "Serialization/BeamJsonUtils.h"



void UOnlineStatusResponses::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UOnlineStatusResponses::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPlayerOnlineStatusResponse*>(TEXT("players"), Players, Serializer);
}

void UOnlineStatusResponses::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPlayerOnlineStatusResponse*>(TEXT("players"), Players, Serializer);		
}

void UOnlineStatusResponses::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UPlayerOnlineStatusResponse*>(Bag->GetArrayField(TEXT("players")), Players, OuterOwner);
}



