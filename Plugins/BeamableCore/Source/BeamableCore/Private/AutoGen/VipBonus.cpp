
#include "BeamableCore/Public/AutoGen/VipBonus.h"

#include "Misc/DefaultValueHelper.h"



void UVipBonus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("currency"), Currency, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("multiplier"), Multiplier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("roundToNearest"), RoundToNearest, Serializer);
}

void UVipBonus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("currency"), Currency, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("multiplier"), Multiplier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("roundToNearest"), RoundToNearest, Serializer);		
}

void UVipBonus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("currency"), Bag, Currency);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("multiplier"), Bag, Multiplier);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("roundToNearest"), Bag, RoundToNearest);
}



