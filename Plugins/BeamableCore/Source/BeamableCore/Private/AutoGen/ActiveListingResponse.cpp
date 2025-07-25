
#include "BeamableCore/Public/AutoGen/ActiveListingResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UActiveListingResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UActiveListingResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storeSymbol"), StoreSymbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UPlayerListingView*>("listing", Listing, Serializer);
}

void UActiveListingResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storeSymbol"), StoreSymbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UPlayerListingView*>("listing", Listing, Serializer);		
}

void UActiveListingResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("storeSymbol"), Bag, StoreSymbol);
	UBeamJsonUtils::DeserializeUObject<UPlayerListingView*>("listing", Bag, Listing, OuterOwner);
}



