
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PrepareNewPlayerRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UPrepareNewPlayerRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userID"), UserID, Serializer);
}

void UPrepareNewPlayerRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userID"), UserID, Serializer);		
}

void UPrepareNewPlayerRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("userID")), UserID);
}



