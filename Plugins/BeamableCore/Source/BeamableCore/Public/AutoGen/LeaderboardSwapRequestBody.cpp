
#include "AutoGen/LeaderboardSwapRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void ULeaderboardSwapRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("winnerId"), &WinnerId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("loserId"), &LoserId, Serializer);
	Serializer->WriteValue(TEXT("swapBase"), SwapBase);
	Serializer->WriteValue(TEXT("delta"), Delta);
}

void ULeaderboardSwapRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("winnerId"), &WinnerId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("loserId"), &LoserId, Serializer);
	Serializer->WriteValue(TEXT("swapBase"), SwapBase);
	Serializer->WriteValue(TEXT("delta"), Delta);		
}

void ULeaderboardSwapRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("winnerId", Bag, WinnerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("loserId", Bag, LoserId, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("swapBase")), SwapBase);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("delta")), Delta);
}