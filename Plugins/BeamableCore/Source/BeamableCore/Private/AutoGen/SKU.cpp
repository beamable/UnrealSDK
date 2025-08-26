
#include "BeamableCore/Public/AutoGen/SKU.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USKU::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("description"), Description, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realPrice"), RealPrice, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("productIds"), ProductIds, Serializer);
}

void USKU::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("description"), Description, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realPrice"), RealPrice, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("productIds"), ProductIds, Serializer);		
}

void USKU::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("description"), Bag, Description);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("realPrice"), Bag, RealPrice);
	UBeamJsonUtils::DeserializeMap<FString>(TEXT("productIds"), Bag, ProductIds, OuterOwner);
}



