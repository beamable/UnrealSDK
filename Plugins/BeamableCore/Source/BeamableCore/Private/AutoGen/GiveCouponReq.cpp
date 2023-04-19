
#include "BeamableCore/Public/AutoGen/GiveCouponReq.h"





void UGiveCouponReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("listing"), Listing);
}

void UGiveCouponReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("listing"), Listing);		
}

void UGiveCouponReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Listing = Bag->GetStringField(TEXT("listing"));
}



