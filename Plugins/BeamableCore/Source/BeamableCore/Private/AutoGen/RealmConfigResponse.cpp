
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"
#include "Serialization/BeamJsonUtils.h"



void URealmConfigResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmConfigResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(TEXT("config"), Config, Serializer);
}

void URealmConfigResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(TEXT("config"), Config, Serializer);		
}

void URealmConfigResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("config")), Config, OuterOwner);
}



