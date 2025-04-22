
#include "BeamableCore/Public/AutoGen/LeaderBoardView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void ULeaderBoardView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lbId"), LbId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("boardSize"), BoardSize, Serializer);
	UBeamJsonUtils::SerializeArray<URankEntry*>(TEXT("rankings"), Rankings, Serializer);
	UBeamJsonUtils::SerializeOptional<URankEntry*>(TEXT("rankgt"), &Rankgt, Serializer);
}

void ULeaderBoardView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lbId"), LbId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("boardSize"), BoardSize, Serializer);
	UBeamJsonUtils::SerializeArray<URankEntry*>(TEXT("rankings"), Rankings, Serializer);
	UBeamJsonUtils::SerializeOptional<URankEntry*>(TEXT("rankgt"), &Rankgt, Serializer);		
}

void ULeaderBoardView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("lbId")), LbId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("boardSize")), BoardSize);
	UBeamJsonUtils::DeserializeArray<URankEntry*>(Bag->GetArrayField(TEXT("rankings")), Rankings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<URankEntry*>("rankgt", Bag, Rankgt, OuterOwner);
}



