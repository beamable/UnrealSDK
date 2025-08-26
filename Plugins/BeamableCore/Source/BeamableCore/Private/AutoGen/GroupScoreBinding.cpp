
#include "BeamableCore/Public/AutoGen/GroupScoreBinding.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupScoreBinding::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("board"), Board, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("derivatives"), Derivatives, Serializer);
}

void UGroupScoreBinding::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("board"), Board, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("derivatives"), Derivatives, Serializer);		
}

void UGroupScoreBinding::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("board"), Bag, Board);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("score"), Bag, Score);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("derivatives"), Bag, Derivatives, OuterOwner);
}



