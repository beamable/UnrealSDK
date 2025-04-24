
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSamlpeStatRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UGetSamlpeStatRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userID"), UserID, Serializer);
}

void UGetSamlpeStatRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userID"), UserID, Serializer);		
}

void UGetSamlpeStatRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("userID")), UserID);
}



