
#include "BeamableCore/Public/AutoGen/MatchMakingMatchesPvpResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UMatchMakingMatchesPvpResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMatchMakingMatchesPvpResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	Serializer->WriteValue(TEXT("totalEntries"), TotalEntries);
	UBeamJsonUtils::SerializeUObject<UMatchMakingRanking*>("playerRank", PlayerRank, Serializer);
	UBeamJsonUtils::SerializeArray<UMatchMakingWindowResp*>(TEXT("windows"), Windows, Serializer);
}

void UMatchMakingMatchesPvpResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	Serializer->WriteValue(TEXT("totalEntries"), TotalEntries);
	UBeamJsonUtils::SerializeUObject<UMatchMakingRanking*>("playerRank", PlayerRank, Serializer);
	UBeamJsonUtils::SerializeArray<UMatchMakingWindowResp*>(TEXT("windows"), Windows, Serializer);		
}

void UMatchMakingMatchesPvpResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Result = Bag->GetStringField(TEXT("result"));
	TotalEntries = Bag->GetIntegerField(TEXT("totalEntries"));
	UBeamJsonUtils::DeserializeUObject<UMatchMakingRanking*>("playerRank", Bag, PlayerRank, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UMatchMakingWindowResp*>(Bag->GetArrayField(TEXT("windows")), Windows, OuterOwner);
}



