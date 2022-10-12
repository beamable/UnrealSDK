
#include "AutoGen/GroupScoreBinding.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UGroupScoreBinding ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("board"), Board);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("derivatives"), Derivatives, Serializer);
	Serializer->WriteValue(TEXT("score"), Score);
}

void UGroupScoreBinding::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("board"), Board);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("derivatives"), Derivatives, Serializer);
	Serializer->WriteValue(TEXT("score"), Score);		
}

void UGroupScoreBinding ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Board = Bag->GetStringField(TEXT("board"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("derivatives")), Derivatives, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("score")), Score);
}