
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerActorNewCustomerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerActorNewCustomerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UAuthResponse*>("token", Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customerId"), CustomerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmId"), RealmId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmName"), RealmName, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("activationPending"), &bActivationPending, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void UCustomerActorNewCustomerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UAuthResponse*>("token", Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customerId"), CustomerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmId"), RealmId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmName"), RealmName, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("activationPending"), &bActivationPending, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void UCustomerActorNewCustomerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UAuthResponse*>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("customerId"), Bag, CustomerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("realmId"), Bag, RealmId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("realmName"), Bag, RealmName);
	UBeamJsonUtils::DeserializeOptional<bool>("activationPending", Bag, bActivationPending, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



