
#include "BeamableCore/Public/AutoGen/RealmConfigChangeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URealmConfigChangeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deletes"), &Deletes, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("upserts"), &Upserts, Serializer);
}

void URealmConfigChangeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deletes"), &Deletes, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("upserts"), &Upserts, Serializer);		
}

void URealmConfigChangeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("deletes", Bag, Deletes, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("upserts", Bag, Upserts, OuterOwner);
}



