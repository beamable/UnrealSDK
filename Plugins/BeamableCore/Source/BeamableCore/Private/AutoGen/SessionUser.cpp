
#include "BeamableCore/Public/AutoGen/SessionUser.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USessionUser::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("email"), Email);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	Serializer->WriteValue(TEXT("username"), Username);
	Serializer->WriteValue(TEXT("lastName"), LastName);
	Serializer->WriteValue(TEXT("firstName"), FirstName);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("lang"), Lang);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
}

void USessionUser::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("email"), Email);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	Serializer->WriteValue(TEXT("username"), Username);
	Serializer->WriteValue(TEXT("lastName"), LastName);
	Serializer->WriteValue(TEXT("firstName"), FirstName);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("lang"), Lang);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);		
}

void USessionUser::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Email = Bag->GetStringField(TEXT("email"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
	Username = Bag->GetStringField(TEXT("username"));
	LastName = Bag->GetStringField(TEXT("lastName"));
	FirstName = Bag->GetStringField(TEXT("firstName"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	Lang = Bag->GetStringField(TEXT("lang"));
	UBeamJsonUtils::DeserializeOptional<FString>("cid", Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("heartbeat", Bag, Heartbeat, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("password", Bag, Password, OuterOwner);
}



