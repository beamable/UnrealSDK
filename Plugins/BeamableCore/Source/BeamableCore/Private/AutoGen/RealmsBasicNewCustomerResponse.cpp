
#include "BeamableCore/Public/AutoGen/RealmsBasicNewCustomerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void URealmsBasicNewCustomerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmsBasicNewCustomerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("activationPending"), bActivationPending, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectName"), ProjectName, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void URealmsBasicNewCustomerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("activationPending"), bActivationPending, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectName"), ProjectName, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void URealmsBasicNewCustomerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("activationPending"), Bag, bActivationPending);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("projectName"), Bag, ProjectName);
	UBeamJsonUtils::DeserializeSemanticType<int64>(TEXT("cid"), Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("pid"), Bag, Pid, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UTokenResponse*>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



