
#include "BeamableCore/Public/AutoGen/LocalizedPriceMap.h"
#include "Serialization/BeamJsonUtils.h"



void ULocalizedPriceMap::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULocalizedPriceMap::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("currency"), Currency, Serializer);
	UBeamJsonUtils::SerializeArray<ULocalizedPrice*>(TEXT("prices"), Prices, Serializer);
}

void ULocalizedPriceMap::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("currency"), Currency, Serializer);
	UBeamJsonUtils::SerializeArray<ULocalizedPrice*>(TEXT("prices"), Prices, Serializer);		
}

void ULocalizedPriceMap::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("currency")), Currency);
	UBeamJsonUtils::DeserializeArray<ULocalizedPrice*>(Bag->GetArrayField(TEXT("prices")), Prices, OuterOwner);
}



