
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PrepareNewPlayerRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UPrepareNewPlayerRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("userID"), UserID);
}

void UPrepareNewPlayerRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("userID"), UserID);		
}

void UPrepareNewPlayerRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("userID")), UserID);
}



