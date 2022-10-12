
#include "AutoGen/ResultResponse.h"



void UResultResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);
}

void UResultResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);		
}

void UResultResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bResult = Bag->GetBoolField(TEXT("result"));
}