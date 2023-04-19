
#include "BeamableCore/Public/AutoGen/NewCustomerRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UNewCustomerRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	Serializer->WriteValue(TEXT("email"), Email);
	Serializer->WriteValue(TEXT("password"), Password);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hierarchy"), &bHierarchy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerName"), &CustomerName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void UNewCustomerRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	Serializer->WriteValue(TEXT("email"), Email);
	Serializer->WriteValue(TEXT("password"), Password);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hierarchy"), &bHierarchy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerName"), &CustomerName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void UNewCustomerRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProjectName = Bag->GetStringField(TEXT("projectName"));
	Email = Bag->GetStringField(TEXT("email"));
	Password = Bag->GetStringField(TEXT("password"));
	UBeamJsonUtils::DeserializeOptional<bool>("hierarchy", Bag, bHierarchy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("customerName", Bag, CustomerName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



