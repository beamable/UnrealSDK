
#include "BeamableCore/Public/AutoGen/Customer.h"
#include "Serialization/BeamJsonUtils.h"




void UCustomer::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeArray<UProject*>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeArray<URealmsBasicAccount*>(TEXT("accounts"), Accounts, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("activationStatus"), &ActivationStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("paymentStatus"), &PaymentStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("image"), &Image, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contact"), &Contact, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("crm_link"), &CrmLink, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void UCustomer::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeArray<UProject*>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeArray<URealmsBasicAccount*>(TEXT("accounts"), Accounts, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("activationStatus"), &ActivationStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("paymentStatus"), &PaymentStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("image"), &Image, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contact"), &Contact, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("crm_link"), &CrmLink, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void UCustomer::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeSemanticType<int64>(TEXT("cid"), Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UProject*>(TEXT("projects"), Bag, Projects, OuterOwner);
	UBeamJsonUtils::DeserializeArray<URealmsBasicAccount*>(TEXT("accounts"), Bag, Accounts, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("activationStatus", Bag, ActivationStatus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("paymentStatus", Bag, PaymentStatus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("image", Bag, Image, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("contact", Bag, Contact, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("updated", Bag, Updated, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("crm_link", Bag, CrmLink, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}



