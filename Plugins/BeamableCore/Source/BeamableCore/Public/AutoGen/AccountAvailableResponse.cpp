
#include "AutoGen/AccountAvailableResponse.h"



void UAccountAvailableResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("available"), bAvailable);
}

void UAccountAvailableResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("available"), bAvailable);		
}

void UAccountAvailableResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bAvailable = Bag->GetBoolField(TEXT("available"));
}