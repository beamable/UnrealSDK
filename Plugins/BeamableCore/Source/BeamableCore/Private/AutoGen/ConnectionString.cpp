
#include "BeamableCore/Public/AutoGen/ConnectionString.h"




void UConnectionString::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UConnectionString::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("connectionString"), ConnectionString);
}

void UConnectionString::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("connectionString"), ConnectionString);		
}

void UConnectionString::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ConnectionString = Bag->GetStringField(TEXT("connectionString"));
}



