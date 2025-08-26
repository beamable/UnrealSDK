
#include "BeamableCore/Public/AutoGen/CustomerActorCustomer.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCustomerActorCustomer::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customerId"), CustomerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamPaymentStatus>(TEXT("paymentStatus"), &PaymentStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamActivationStatus>(TEXT("activationStatus"), &ActivationStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contact"), &Contact, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URealm*>, URealm*>(TEXT("realms"), &Realms, Serializer);
}

void UCustomerActorCustomer::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customerId"), CustomerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamPaymentStatus>(TEXT("paymentStatus"), &PaymentStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamActivationStatus>(TEXT("activationStatus"), &ActivationStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contact"), &Contact, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URealm*>, URealm*>(TEXT("realms"), &Realms, Serializer);		
}

void UCustomerActorCustomer::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("customerId"), Bag, CustomerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EBeamPaymentStatus>("paymentStatus", Bag, PaymentStatus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EBeamActivationStatus>("activationStatus", Bag, ActivationStatus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("contact", Bag, Contact, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("updated", Bag, Updated, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URealm*>, URealm*>("realms", Bag, Realms, OuterOwner);
}



