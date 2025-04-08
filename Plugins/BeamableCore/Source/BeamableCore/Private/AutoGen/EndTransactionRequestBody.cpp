
#include "BeamableCore/Public/AutoGen/EndTransactionRequestBody.h"





void UEndTransactionRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("transaction"), Transaction);
}

void UEndTransactionRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("transaction"), Transaction);		
}

void UEndTransactionRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("transaction")), Transaction);
}



