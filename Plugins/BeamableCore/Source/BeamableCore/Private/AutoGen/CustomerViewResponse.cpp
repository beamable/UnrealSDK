
#include "BeamableCore/Public/AutoGen/CustomerViewResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerViewResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerViewResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UCustomerView*>("customer", Customer, Serializer);
}

void UCustomerViewResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UCustomerView*>("customer", Customer, Serializer);		
}

void UCustomerViewResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UCustomerView*>("customer", Bag, Customer, OuterOwner);
}



