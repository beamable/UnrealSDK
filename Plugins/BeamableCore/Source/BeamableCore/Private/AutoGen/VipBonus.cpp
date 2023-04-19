
#include "BeamableCore/Public/AutoGen/VipBonus.h"

#include "Misc/DefaultValueHelper.h"



void UVipBonus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("currency"), Currency);
	Serializer->WriteValue(TEXT("multiplier"), Multiplier);
	Serializer->WriteValue(TEXT("roundToNearest"), RoundToNearest);
}

void UVipBonus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("currency"), Currency);
	Serializer->WriteValue(TEXT("multiplier"), Multiplier);
	Serializer->WriteValue(TEXT("roundToNearest"), RoundToNearest);		
}

void UVipBonus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Currency = Bag->GetStringField(TEXT("currency"));
	Multiplier = Bag->GetNumberField(TEXT("multiplier"));
	RoundToNearest = Bag->GetIntegerField(TEXT("roundToNearest"));
}



