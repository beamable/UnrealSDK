
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("code"), Bag, Code);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("password"), Bag, Password);
}



