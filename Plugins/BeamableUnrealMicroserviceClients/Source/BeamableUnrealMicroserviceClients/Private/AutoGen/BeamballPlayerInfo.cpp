
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballPlayerInfo.h"

#include "Misc/DefaultValueHelper.h"



void UBeamballPlayerInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("GamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("Life"), Life, Serializer);
}

void UBeamballPlayerInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("GamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("Life"), Life, Serializer);		
}

void UBeamballPlayerInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("GamerTag"), Bag, GamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Life"), Bag, Life);
}



