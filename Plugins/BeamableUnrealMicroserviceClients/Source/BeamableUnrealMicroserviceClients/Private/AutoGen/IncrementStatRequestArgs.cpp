
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/IncrementStatRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UIncrementStatRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("userID"), UserID);
}

void UIncrementStatRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("userID"), UserID);		
}

void UIncrementStatRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("userID")), UserID);
}



