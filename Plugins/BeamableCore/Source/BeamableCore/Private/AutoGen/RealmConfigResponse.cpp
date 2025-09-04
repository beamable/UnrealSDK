
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"
#include "Serialization/BeamJsonUtils.h"



void URealmConfigResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmConfigResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("config"), &Config, Serializer);
}

void URealmConfigResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("config"), &Config, Serializer);		
}

void URealmConfigResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("config", Bag, Config, OuterOwner);
}



