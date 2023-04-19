
#include "BeamableCore/Public/AutoGen/AccountRegistration.h"





void UAccountRegistration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	Serializer->WriteValue(TEXT("password"), Password);
}

void UAccountRegistration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	Serializer->WriteValue(TEXT("password"), Password);		
}

void UAccountRegistration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Email = Bag->GetStringField(TEXT("email"));
	Password = Bag->GetStringField(TEXT("password"));
}



