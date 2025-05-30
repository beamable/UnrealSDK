
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AddRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UAddRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("a"), A);
	Serializer->WriteValue(TEXT("b"), B);
}

void UAddRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("a"), A);
	Serializer->WriteValue(TEXT("b"), B);		
}

void UAddRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	A = Bag->GetIntegerField(TEXT("a"));
	B = Bag->GetIntegerField(TEXT("b"));
}



