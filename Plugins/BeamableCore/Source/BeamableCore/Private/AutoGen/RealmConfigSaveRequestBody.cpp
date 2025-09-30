
#include "BeamableCore/Public/AutoGen/RealmConfigSaveRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URealmConfigSaveRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("config"), &Config, Serializer);
}

void URealmConfigSaveRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("config"), &Config, Serializer);		
}

void URealmConfigSaveRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("config", Bag, Config, OuterOwner);
}



