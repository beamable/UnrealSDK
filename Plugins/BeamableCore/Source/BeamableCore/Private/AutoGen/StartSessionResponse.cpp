
#include "BeamableCore/Public/AutoGen/StartSessionResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UStartSessionResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStartSessionResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeOptional<UGamerTag*>(TEXT("gamer"), &Gamer, Serializer);
}

void UStartSessionResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeOptional<UGamerTag*>(TEXT("gamer"), &Gamer, Serializer);		
}

void UStartSessionResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("result")), Result);
	UBeamJsonUtils::DeserializeOptional<UGamerTag*>("gamer", Bag, Gamer, OuterOwner);
}



