
#include "BeamableCore/Public/AutoGen/RealmRolesReport.h"
#include "Serialization/BeamJsonUtils.h"




void URealmRolesReport::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("realmName"), RealmName);
	Serializer->WriteValue(TEXT("realmDisplayName"), RealmDisplayName);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("roles"), Roles, Serializer);
}

void URealmRolesReport::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("realmName"), RealmName);
	Serializer->WriteValue(TEXT("realmDisplayName"), RealmDisplayName);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("roles"), Roles, Serializer);		
}

void URealmRolesReport::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	RealmName = Bag->GetStringField(TEXT("realmName"));
	RealmDisplayName = Bag->GetStringField(TEXT("realmDisplayName"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("roles")), Roles, OuterOwner);
}



