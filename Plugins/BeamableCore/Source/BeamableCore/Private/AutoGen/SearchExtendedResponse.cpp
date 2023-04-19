
#include "BeamableCore/Public/AutoGen/SearchExtendedResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USearchExtendedResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USearchExtendedResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FMapOfString>(TEXT("gamerStats"), GamerStats, Serializer);
}

void USearchExtendedResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FMapOfString>(TEXT("gamerStats"), GamerStats, Serializer);		
}

void USearchExtendedResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<FMapOfString>(Bag->GetObjectField(TEXT("gamerStats")), GamerStats, OuterOwner);
}



