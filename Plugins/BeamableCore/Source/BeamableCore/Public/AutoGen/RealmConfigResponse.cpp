
#include "AutoGen/RealmConfigResponse.h"
#include "Serialization/BeamJsonUtils.h"


void URealmConfigResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(TEXT("config"), Config, Serializer);
}

void URealmConfigResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(TEXT("config"), Config, Serializer);		
}

void URealmConfigResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("config")), Config, OuterOwner);
}