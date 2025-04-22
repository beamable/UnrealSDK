
#include "BeamableCore/Public/AutoGen/LeaderboardSwapRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void ULeaderboardSwapRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("swapBase"), SwapBase, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("delta"), Delta, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("winnerId"), &WinnerId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("loserId"), &LoserId, Serializer);
}

void ULeaderboardSwapRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("swapBase"), SwapBase, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("delta"), Delta, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("winnerId"), &WinnerId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("loserId"), &LoserId, Serializer);		
}

void ULeaderboardSwapRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("swapBase")), SwapBase);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("delta")), Delta);
	UBeamJsonUtils::DeserializeOptional<int64>("winnerId", Bag, WinnerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("loserId", Bag, LoserId, OuterOwner);
}



