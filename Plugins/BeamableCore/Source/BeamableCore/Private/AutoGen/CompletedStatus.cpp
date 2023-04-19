
#include "BeamableCore/Public/AutoGen/CompletedStatus.h"

#include "Misc/DefaultValueHelper.h"



void UCompletedStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("cycle"), Cycle);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("delta"), Delta);
}

void UCompletedStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("cycle"), Cycle);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("delta"), Delta);		
}

void UCompletedStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Cycle = Bag->GetIntegerField(TEXT("cycle"));
	Tier = Bag->GetIntegerField(TEXT("tier"));
	Stage = Bag->GetIntegerField(TEXT("stage"));
	Delta = Bag->GetIntegerField(TEXT("delta"));
}



