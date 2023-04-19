
#include "BeamableCore/Public/AutoGen/RealmConfigSaveRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URealmConfigSaveRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(TEXT("config"), Config, Serializer);
}

void URealmConfigSaveRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(TEXT("config"), Config, Serializer);		
}

void URealmConfigSaveRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("config")), Config, OuterOwner);
}



