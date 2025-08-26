
#include "BeamableCore/Public/AutoGen/RealmsBasicNewCustomerRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URealmsBasicNewCustomerRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectName"), ProjectName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hierarchy"), &bHierarchy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerName"), &CustomerName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void URealmsBasicNewCustomerRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectName"), ProjectName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hierarchy"), &bHierarchy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerName"), &CustomerName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void URealmsBasicNewCustomerRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("projectName"), Bag, ProjectName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("email"), Bag, Email);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("password"), Bag, Password);
	UBeamJsonUtils::DeserializeOptional<bool>("hierarchy", Bag, bHierarchy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("customerName", Bag, CustomerName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



