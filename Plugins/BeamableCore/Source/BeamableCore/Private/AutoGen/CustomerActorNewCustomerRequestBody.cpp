
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCustomerActorNewCustomerRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmName"), RealmName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hierarchy"), &bHierarchy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerName"), &CustomerName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void UCustomerActorNewCustomerRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmName"), RealmName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hierarchy"), &bHierarchy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerName"), &CustomerName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void UCustomerActorNewCustomerRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("realmName"), Bag, RealmName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("email"), Bag, Email);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("password"), Bag, Password);
	UBeamJsonUtils::DeserializeOptional<bool>("hierarchy", Bag, bHierarchy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("customerName", Bag, CustomerName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



