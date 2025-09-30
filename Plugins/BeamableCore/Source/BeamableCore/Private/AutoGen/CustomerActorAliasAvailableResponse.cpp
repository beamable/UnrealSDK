
#include "BeamableCore/Public/AutoGen/CustomerActorAliasAvailableResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerActorAliasAvailableResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerActorAliasAvailableResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("available"), bAvailable, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerId"), &CustomerId, Serializer);
}

void UCustomerActorAliasAvailableResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("available"), bAvailable, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerId"), &CustomerId, Serializer);		
}

void UCustomerActorAliasAvailableResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("alias"), Bag, Alias);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("available"), Bag, bAvailable);
	UBeamJsonUtils::DeserializeOptional<FString>("customerId", Bag, CustomerId, OuterOwner);
}



