
#include "BeamableCore/Public/AutoGen/ListLeaderBoardViewResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UListLeaderBoardViewResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UListLeaderBoardViewResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	UBeamJsonUtils::SerializeArray<ULeaderBoardView*>(TEXT("lbs"), Lbs, Serializer);
}

void UListLeaderBoardViewResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	UBeamJsonUtils::SerializeArray<ULeaderBoardView*>(TEXT("lbs"), Lbs, Serializer);		
}

void UListLeaderBoardViewResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Result = Bag->GetStringField(TEXT("result"));
	UBeamJsonUtils::DeserializeArray<ULeaderBoardView*>(Bag->GetArrayField(TEXT("lbs")), Lbs, OuterOwner);
}



