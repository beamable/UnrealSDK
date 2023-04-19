
#include "BeamableCore/Public/AutoGen/EventInventoryRewardCurrency.h"

#include "Misc/DefaultValueHelper.h"



void UEventInventoryRewardCurrency::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("amount"), Amount);
}

void UEventInventoryRewardCurrency::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("amount"), Amount);		
}

void UEventInventoryRewardCurrency::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
}



