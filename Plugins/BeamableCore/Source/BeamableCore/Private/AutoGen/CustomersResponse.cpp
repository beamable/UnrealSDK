
#include "BeamableCore/Public/AutoGen/CustomersResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomersResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomersResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCustomer*>(TEXT("result"), Result, Serializer);
}

void UCustomersResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCustomer*>(TEXT("result"), Result, Serializer);		
}

void UCustomersResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UCustomer*>(Bag->GetArrayField(TEXT("result")), Result, OuterOwner);
}



