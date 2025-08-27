
#include "BeamableCore/Public/AutoGen/CustomerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UCustomer*>("customer", Customer, Serializer);
}

void UCustomerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UCustomer*>("customer", Customer, Serializer);		
}

void UCustomerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UCustomer*>("customer", Bag, Customer, OuterOwner);
}



