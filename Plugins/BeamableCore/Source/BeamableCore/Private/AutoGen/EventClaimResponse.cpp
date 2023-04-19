
#include "BeamableCore/Public/AutoGen/EventClaimResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UEventClaimResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UEventClaimResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UEventPlayerStateView*>("view", View, Serializer);
	Serializer->WriteValue(TEXT("gameRspJson"), GameRspJson);
}

void UEventClaimResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UEventPlayerStateView*>("view", View, Serializer);
	Serializer->WriteValue(TEXT("gameRspJson"), GameRspJson);		
}

void UEventClaimResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UEventPlayerStateView*>("view", Bag, View, OuterOwner);
	GameRspJson = Bag->GetStringField(TEXT("gameRspJson"));
}



