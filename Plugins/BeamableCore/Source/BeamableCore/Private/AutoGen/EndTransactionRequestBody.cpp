
#include "BeamableCore/Public/AutoGen/EndTransactionRequestBody.h"





void UEndTransactionRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("transaction"), Transaction, Serializer);
}

void UEndTransactionRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("transaction"), Transaction, Serializer);		
}

void UEndTransactionRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("transaction")), Transaction);
}



