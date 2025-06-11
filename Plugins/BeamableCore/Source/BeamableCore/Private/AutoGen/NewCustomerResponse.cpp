
#include "BeamableCore/Public/AutoGen/NewCustomerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UNewCustomerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UNewCustomerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("activationPending"), bActivationPending, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectName"), ProjectName, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void UNewCustomerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("activationPending"), bActivationPending, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectName"), ProjectName, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void UNewCustomerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("activationPending")), bActivationPending);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("projectName")), ProjectName);
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("cid")), Cid, OuterOwner);
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("pid")), Pid, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UTokenResponse*>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



