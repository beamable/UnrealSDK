
#include "AutoGen/ConnectionString.h"



void UConnectionString ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("connectionString"), ConnectionString);
}

void UConnectionString::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("connectionString"), ConnectionString);		
}

void UConnectionString ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ConnectionString = Bag->GetStringField(TEXT("connectionString"));
}