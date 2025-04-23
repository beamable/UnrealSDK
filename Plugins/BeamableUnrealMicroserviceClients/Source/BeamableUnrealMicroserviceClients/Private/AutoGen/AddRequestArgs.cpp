
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AddRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UAddRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("a"), A, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("b"), B, Serializer);
}

void UAddRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("a"), A, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("b"), B, Serializer);		
}

void UAddRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("a")), A);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("b")), B);
}



