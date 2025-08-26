
#include "BeamableCore/Public/AutoGen/RealmsBasicCustomersResponse.h"
#include "Serialization/BeamJsonUtils.h"



void URealmsBasicCustomersResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmsBasicCustomersResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URealmsBasicCustomer*>(TEXT("result"), Result, Serializer);
}

void URealmsBasicCustomersResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URealmsBasicCustomer*>(TEXT("result"), Result, Serializer);		
}

void URealmsBasicCustomersResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<URealmsBasicCustomer*>(TEXT("result"), Bag, Result, OuterOwner);
}



