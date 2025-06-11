
#include "BeamableCore/Public/AutoGen/SetPresenceStatusRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USetPresenceStatusRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamPresenceStatus>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
}

void USetPresenceStatusRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamPresenceStatus>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);		
}

void USetPresenceStatusRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<EBeamPresenceStatus>("status", Bag, Status, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
}



