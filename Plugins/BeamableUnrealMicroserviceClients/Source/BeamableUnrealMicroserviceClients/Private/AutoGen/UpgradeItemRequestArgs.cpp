
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UpgradeItemRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UUpgradeItemRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("userID"), UserID);
	Serializer->WriteValue(TEXT("itemInstaceID"), ItemInstaceID);
}

void UUpgradeItemRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("userID"), UserID);
	Serializer->WriteValue(TEXT("itemInstaceID"), ItemInstaceID);		
}

void UUpgradeItemRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("userID")), UserID);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("itemInstaceID")), ItemInstaceID);
}



