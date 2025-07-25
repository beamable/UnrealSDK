
#include "BeamableCore/Public/AutoGen/UpdateListingCooldownRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UUpdateListingCooldownRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cooldownReduction"), CooldownReduction, Serializer);
}

void UUpdateListingCooldownRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cooldownReduction"), CooldownReduction, Serializer);		
}

void UUpdateListingCooldownRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("cooldownReduction"), Bag, CooldownReduction);
}



