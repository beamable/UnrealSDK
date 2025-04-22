
#include "BeamableCore/Public/AutoGen/GiveCouponReq.h"





void UGiveCouponReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("listing"), Listing, Serializer);
}

void UGiveCouponReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("listing"), Listing, Serializer);		
}

void UGiveCouponReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("listing")), Listing);
}



