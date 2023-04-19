
#include "BeamableCore/Public/AutoGen/GroupScoreBinding.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupScoreBinding::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("board"), Board);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("derivatives"), Derivatives, Serializer);
}

void UGroupScoreBinding::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("board"), Board);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("derivatives"), Derivatives, Serializer);		
}

void UGroupScoreBinding::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Board = Bag->GetStringField(TEXT("board"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("score")), Score);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("derivatives")), Derivatives, OuterOwner);
}



