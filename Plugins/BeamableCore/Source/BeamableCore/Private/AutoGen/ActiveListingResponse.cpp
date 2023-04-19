
#include "BeamableCore/Public/AutoGen/ActiveListingResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UActiveListingResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UActiveListingResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("storeSymbol"), StoreSymbol);
	UBeamJsonUtils::SerializeUObject<UPlayerListingView*>("listing", Listing, Serializer);
}

void UActiveListingResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("storeSymbol"), StoreSymbol);
	UBeamJsonUtils::SerializeUObject<UPlayerListingView*>("listing", Listing, Serializer);		
}

void UActiveListingResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	StoreSymbol = Bag->GetStringField(TEXT("storeSymbol"));
	UBeamJsonUtils::DeserializeUObject<UPlayerListingView*>("listing", Bag, Listing, OuterOwner);
}



