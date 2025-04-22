
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"
#include "Serialization/BeamJsonUtils.h"



void ULeaderBoardViewResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULeaderBoardViewResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("lb", Lb, Serializer);
}

void ULeaderBoardViewResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("lb", Lb, Serializer);		
}

void ULeaderBoardViewResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("result")), Result);
	UBeamJsonUtils::DeserializeUObject<ULeaderBoardView*>("lb", Bag, Lb, OuterOwner);
}



