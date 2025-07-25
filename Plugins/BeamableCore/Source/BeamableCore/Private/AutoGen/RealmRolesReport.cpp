
#include "BeamableCore/Public/AutoGen/RealmRolesReport.h"
#include "Serialization/BeamJsonUtils.h"




void URealmRolesReport::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmName"), RealmName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmDisplayName"), RealmDisplayName, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("roles"), Roles, Serializer);
}

void URealmRolesReport::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmName"), RealmName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmDisplayName"), RealmDisplayName, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("roles"), Roles, Serializer);		
}

void URealmRolesReport::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("realmName"), Bag, RealmName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("realmDisplayName"), Bag, RealmDisplayName);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("roles"), Bag, Roles, OuterOwner);
}



