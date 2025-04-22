
#include "BeamableCore/Public/AutoGen/ReportPurchaseRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UReportPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("listingId"), ListingId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("free"), &bFree, Serializer);
}

void UReportPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("listingId"), ListingId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("free"), &bFree, Serializer);		
}

void UReportPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("listingId")), ListingId);
	UBeamJsonUtils::DeserializeOptional<bool>("free", Bag, bFree, OuterOwner);
}



