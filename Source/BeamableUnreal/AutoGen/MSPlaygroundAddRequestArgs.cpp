
#include "BeamableUnreal\AutoGen/MSPlaygroundAddRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UMSPlaygroundAddRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("a"), A);
	Serializer->WriteValue(TEXT("b"), B);
}

void UMSPlaygroundAddRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("a"), A);
	Serializer->WriteValue(TEXT("b"), B);		
}

void UMSPlaygroundAddRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	A = Bag->GetIntegerField(TEXT("a"));
	B = Bag->GetIntegerField(TEXT("b"));
}



