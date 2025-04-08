
#include "BeamableCore/Public/AutoGen/EmailUpdateConfirmation.h"





void UEmailUpdateConfirmation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("code"), Code);
	Serializer->WriteValue(TEXT("password"), Password);
}

void UEmailUpdateConfirmation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("code"), Code);
	Serializer->WriteValue(TEXT("password"), Password);		
}

void UEmailUpdateConfirmation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("code")), Code);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("password")), Password);
}



