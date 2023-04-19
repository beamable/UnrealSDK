
#include "BeamableCore/Public/AutoGen/PlayerIdRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPlayerIdRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
}

void UPlayerIdRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UPlayerIdRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("playerId")), PlayerId, OuterOwner);
}



