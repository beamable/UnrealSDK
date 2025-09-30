
#include "BeamableCore/Public/AutoGen/CustomerActorCustomersResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerActorCustomersResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerActorCustomersResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UCustomerActorCustomer*>, UCustomerActorCustomer*>(TEXT("customers"), &Customers, Serializer);
}

void UCustomerActorCustomersResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UCustomerActorCustomer*>, UCustomerActorCustomer*>(TEXT("customers"), &Customers, Serializer);		
}

void UCustomerActorCustomersResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UCustomerActorCustomer*>, UCustomerActorCustomer*>("customers", Bag, Customers, OuterOwner);
}



