
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
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalEntries"), TotalEntries, Serializer);
	UBeamJsonUtils::SerializeUObject<UMatchMakingRanking*>("playerRank", PlayerRank, Serializer);
	UBeamJsonUtils::SerializeArray<UMatchMakingWindowResp*>(TEXT("windows"), Windows, Serializer);
}

void UMatchMakingMatchesPvpResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalEntries"), TotalEntries, Serializer);
	UBeamJsonUtils::SerializeUObject<UMatchMakingRanking*>("playerRank", PlayerRank, Serializer);
	UBeamJsonUtils::SerializeArray<UMatchMakingWindowResp*>(TEXT("windows"), Windows, Serializer);		
}

void UMatchMakingMatchesPvpResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("result")), Result);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("totalEntries")), TotalEntries);
	UBeamJsonUtils::DeserializeUObject<UMatchMakingRanking*>("playerRank", Bag, PlayerRank, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UMatchMakingWindowResp*>(Bag->GetArrayField(TEXT("windows")), Windows, OuterOwner);
}



