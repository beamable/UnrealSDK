
#include "BeamableCore/Public/AutoGen/CompletedStatus.h"

#include "Misc/DefaultValueHelper.h"



void UCompletedStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cycle"), Cycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("delta"), Delta, Serializer);
}

void UCompletedStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cycle"), Cycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("delta"), Delta, Serializer);		
}

void UCompletedStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cycle")), Cycle);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("tier")), Tier);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("stage")), Stage);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("delta")), Delta);
}



