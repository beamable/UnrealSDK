
#include "AutoGen/LeaderBoardViewResponse.h"
#include "Serialization/BeamJsonUtils.h"


void ULeaderBoardViewResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("lb", Lb, Serializer);
}

void ULeaderBoardViewResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("lb", Lb, Serializer);		
}

void ULeaderBoardViewResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Result = Bag->GetStringField(TEXT("result"));
	UBeamJsonUtils::DeserializeUObject<ULeaderBoardView*>("lb", Bag, Lb, OuterOwner);
}