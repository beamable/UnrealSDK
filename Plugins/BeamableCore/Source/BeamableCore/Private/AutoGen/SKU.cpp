
#include "BeamableCore/Public/AutoGen/SKU.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USKU::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("description"), Description);
	Serializer->WriteValue(TEXT("realPrice"), RealPrice);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("productIds"), ProductIds, Serializer);
}

void USKU::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("description"), Description);
	Serializer->WriteValue(TEXT("realPrice"), RealPrice);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("productIds"), ProductIds, Serializer);		
}

void USKU::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Description = Bag->GetStringField(TEXT("description"));
	RealPrice = Bag->GetIntegerField(TEXT("realPrice"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("productIds")), ProductIds, OuterOwner);
}



