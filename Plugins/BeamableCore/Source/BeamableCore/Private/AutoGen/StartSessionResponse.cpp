
#include "BeamableCore/Public/AutoGen/StartSessionResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UStartSessionResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStartSessionResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	UBeamJsonUtils::SerializeOptional<UGamerTag*>(TEXT("gamer"), &Gamer, Serializer);
}

void UStartSessionResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	UBeamJsonUtils::SerializeOptional<UGamerTag*>(TEXT("gamer"), &Gamer, Serializer);		
}

void UStartSessionResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Result = Bag->GetStringField(TEXT("result"));
	UBeamJsonUtils::DeserializeOptional<UGamerTag*>("gamer", Bag, Gamer, OuterOwner);
}



