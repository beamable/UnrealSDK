
#include "BeamableCore/Public/AutoGen/LocalizedPriceMap.h"
#include "Serialization/BeamJsonUtils.h"



void ULocalizedPriceMap::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULocalizedPriceMap::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("currency"), Currency);
	UBeamJsonUtils::SerializeArray<ULocalizedPrice*>(TEXT("prices"), Prices, Serializer);
}

void ULocalizedPriceMap::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("currency"), Currency);
	UBeamJsonUtils::SerializeArray<ULocalizedPrice*>(TEXT("prices"), Prices, Serializer);		
}

void ULocalizedPriceMap::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Currency = Bag->GetStringField(TEXT("currency"));
	UBeamJsonUtils::DeserializeArray<ULocalizedPrice*>(Bag->GetArrayField(TEXT("prices")), Prices, OuterOwner);
}



