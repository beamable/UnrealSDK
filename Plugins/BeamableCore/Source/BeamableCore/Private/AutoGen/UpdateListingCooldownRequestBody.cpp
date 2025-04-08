
#include "BeamableCore/Public/AutoGen/UpdateListingCooldownRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UUpdateListingCooldownRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("cooldownReduction"), CooldownReduction);
}

void UUpdateListingCooldownRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("cooldownReduction"), CooldownReduction);		
}

void UUpdateListingCooldownRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cooldownReduction")), CooldownReduction);
}



