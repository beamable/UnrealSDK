
#include "BeamableCore/Public/AutoGen/EmailUpdateConfirmation.h"





void UEmailUpdateConfirmation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
}

void UEmailUpdateConfirmation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);		
}

void UEmailUpdateConfirmation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("code")), Code);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("password")), Password);
}



