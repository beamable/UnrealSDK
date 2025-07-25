
#include "BeamableCore/Public/AutoGen/SessionUser.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USessionUser::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("username"), Username, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastName"), LastName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("firstName"), FirstName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lang"), Lang, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
}

void USessionUser::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("username"), Username, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastName"), LastName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("firstName"), FirstName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lang"), Lang, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);		
}

void USessionUser::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("email"), Bag, Email);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gamerTag"), Bag, GamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("username"), Bag, Username);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lastName"), Bag, LastName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("firstName"), Bag, FirstName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lang"), Bag, Lang);
	UBeamJsonUtils::DeserializeOptional<FString>("cid", Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("heartbeat", Bag, Heartbeat, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("password", Bag, Password, OuterOwner);
}



