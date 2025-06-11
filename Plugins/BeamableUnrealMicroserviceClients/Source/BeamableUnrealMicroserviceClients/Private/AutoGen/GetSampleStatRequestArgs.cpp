
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSampleStatRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UGetSampleStatRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
}

void UGetSampleStatRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);		
}

void UGetSampleStatRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
}



