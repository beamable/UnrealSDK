
#include "AutoGen/GetGameRequestBody.h"





void UGetGameRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rootPID"), RootPID);
}

void UGetGameRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rootPID"), RootPID);		
}

void UGetGameRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	RootPID = Bag->GetStringField(TEXT("rootPID"));
}