
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cycle")), Cycle);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("tier")), Tier);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("stage")), Stage);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("delta")), Delta);
}



