
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
	Symbol = Bag->GetStringField(TEXT("symbol"));
	CooldownReduction = Bag->GetIntegerField(TEXT("cooldownReduction"));
}



