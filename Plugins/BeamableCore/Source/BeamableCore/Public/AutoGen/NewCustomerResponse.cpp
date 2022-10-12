
#include "AutoGen/NewCustomerResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UNewCustomerResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	Serializer->WriteValue(TEXT("cid"), Cid);
	Serializer->WriteValue(TEXT("pid"), Pid);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);
}

void UNewCustomerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	Serializer->WriteValue(TEXT("cid"), Cid);
	Serializer->WriteValue(TEXT("pid"), Pid);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);		
}

void UNewCustomerResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	ProjectName = Bag->GetStringField(TEXT("projectName"));
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("cid")), Cid);
	Pid = Bag->GetStringField(TEXT("pid"));
	UBeamJsonUtils::DeserializeUObject<UTokenResponse*>("token", Bag, Token, OuterOwner);
}