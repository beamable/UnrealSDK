
#include "BeamableCore/Public/AutoGen/GetGamesResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetGamesResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetGamesResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<URealmView*>, URealmView*>(TEXT("realms"), &Realms, Serializer);
}

void UGetGamesResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<URealmView*>, URealmView*>(TEXT("realms"), &Realms, Serializer);		
}

void UGetGamesResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<URealmView*>, URealmView*>("realms", Bag, Realms, OuterOwner);
}



