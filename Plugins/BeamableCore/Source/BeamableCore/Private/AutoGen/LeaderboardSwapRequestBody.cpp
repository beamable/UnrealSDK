
#include "BeamableCore/Public/AutoGen/LeaderboardSwapRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void ULeaderboardSwapRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("swapBase"), SwapBase);
	Serializer->WriteValue(TEXT("delta"), Delta);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("winnerId"), &WinnerId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("loserId"), &LoserId, Serializer);
}

void ULeaderboardSwapRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("swapBase"), SwapBase);
	Serializer->WriteValue(TEXT("delta"), Delta);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("winnerId"), &WinnerId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("loserId"), &LoserId, Serializer);		
}

void ULeaderboardSwapRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("swapBase")), SwapBase);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("delta")), Delta);
	UBeamJsonUtils::DeserializeOptional<int64>("winnerId", Bag, WinnerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("loserId", Bag, LoserId, OuterOwner);
}



