
#include "BeamableCore/Public/AutoGen/Promotable.h"

#include "Misc/DefaultValueHelper.h"



void UPromotable::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdAt"), CreatedAt, Serializer);
}

void UPromotable::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdAt"), CreatedAt, Serializer);		
}

void UPromotable::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("createdAt"), Bag, CreatedAt);
}



