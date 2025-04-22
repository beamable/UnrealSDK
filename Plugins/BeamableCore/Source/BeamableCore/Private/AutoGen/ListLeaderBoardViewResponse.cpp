
#include "BeamableCore/Public/AutoGen/ListLeaderBoardViewResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UListLeaderBoardViewResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UListLeaderBoardViewResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeArray<ULeaderBoardView*>(TEXT("lbs"), Lbs, Serializer);
}

void UListLeaderBoardViewResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeArray<ULeaderBoardView*>(TEXT("lbs"), Lbs, Serializer);		
}

void UListLeaderBoardViewResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("result")), Result);
	UBeamJsonUtils::DeserializeArray<ULeaderBoardView*>(Bag->GetArrayField(TEXT("lbs")), Lbs, OuterOwner);
}



