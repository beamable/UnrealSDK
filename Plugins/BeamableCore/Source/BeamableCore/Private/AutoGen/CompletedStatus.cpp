
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("cycle"), Bag, Cycle);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tier"), Bag, Tier);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stage"), Bag, Stage);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("delta"), Bag, Delta);
}



