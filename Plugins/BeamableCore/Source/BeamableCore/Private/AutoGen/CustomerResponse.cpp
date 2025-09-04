
#include "BeamableCore/Public/AutoGen/CustomerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<URealmsBasicCustomer*>("customer", Customer, Serializer);
}

void UCustomerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<URealmsBasicCustomer*>("customer", Customer, Serializer);		
}

void UCustomerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<URealmsBasicCustomer*>("customer", Bag, Customer, OuterOwner);
}



