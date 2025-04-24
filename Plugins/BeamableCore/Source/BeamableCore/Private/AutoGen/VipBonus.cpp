
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("currency")), Currency);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("multiplier")), Multiplier);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("roundToNearest")), RoundToNearest);
}



