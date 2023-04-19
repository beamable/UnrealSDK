
#include "BeamableCore/Public/AutoGen/NewCustomerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UNewCustomerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UNewCustomerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void UNewCustomerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void UNewCustomerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	ProjectName = Bag->GetStringField(TEXT("projectName"));
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("cid")), Cid, OuterOwner);
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("pid")), Pid, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UTokenResponse*>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



