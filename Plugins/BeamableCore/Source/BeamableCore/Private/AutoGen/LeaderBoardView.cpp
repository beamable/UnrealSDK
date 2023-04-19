
#include "BeamableCore/Public/AutoGen/LeaderBoardView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void ULeaderBoardView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lbId"), LbId);
	Serializer->WriteValue(TEXT("boardSize"), BoardSize);
	UBeamJsonUtils::SerializeArray<URankEntry*>(TEXT("rankings"), Rankings, Serializer);
	UBeamJsonUtils::SerializeOptional<URankEntry*>(TEXT("rankgt"), &Rankgt, Serializer);
}

void ULeaderBoardView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lbId"), LbId);
	Serializer->WriteValue(TEXT("boardSize"), BoardSize);
	UBeamJsonUtils::SerializeArray<URankEntry*>(TEXT("rankings"), Rankings, Serializer);
	UBeamJsonUtils::SerializeOptional<URankEntry*>(TEXT("rankgt"), &Rankgt, Serializer);		
}

void ULeaderBoardView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	LbId = Bag->GetStringField(TEXT("lbId"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("boardSize")), BoardSize);
	UBeamJsonUtils::DeserializeArray<URankEntry*>(Bag->GetArrayField(TEXT("rankings")), Rankings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<URankEntry*>("rankgt", Bag, Rankgt, OuterOwner);
}



