
#include "BeamableCore/Public/AutoGen/GetTotalCouponResponse.h"

#include "Misc/DefaultValueHelper.h"


void UGetTotalCouponResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetTotalCouponResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("count"), Count, Serializer);
}

void UGetTotalCouponResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("count"), Count, Serializer);		
}

void UGetTotalCouponResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("count")), Count);
}



