
#include "BeamableCore/Public/AutoGen/RealmAssociation.h"
#include "Serialization/BeamJsonUtils.h"




void URealmAssociation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);
}

void URealmAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);		
}

void URealmAssociation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("playerId", Bag, PlayerId, OuterOwner);
}



