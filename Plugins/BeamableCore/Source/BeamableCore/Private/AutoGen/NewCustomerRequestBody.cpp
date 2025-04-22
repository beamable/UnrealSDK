
#include "BeamableCore/Public/AutoGen/NewCustomerRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UNewCustomerRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectName"), ProjectName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hierarchy"), &bHierarchy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerName"), &CustomerName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void UNewCustomerRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectName"), ProjectName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hierarchy"), &bHierarchy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerName"), &CustomerName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void UNewCustomerRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("projectName")), ProjectName);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("email")), Email);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("password")), Password);
	UBeamJsonUtils::DeserializeOptional<bool>("hierarchy", Bag, bHierarchy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("customerName", Bag, CustomerName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



