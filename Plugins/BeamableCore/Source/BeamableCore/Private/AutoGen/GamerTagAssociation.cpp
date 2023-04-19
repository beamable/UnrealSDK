
#include "BeamableCore/Public/AutoGen/GamerTagAssociation.h"
#include "Serialization/BeamJsonUtils.h"




void UGamerTagAssociation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("projectId"), &ProjectId, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
}

void UGamerTagAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("projectId"), &ProjectId, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("gamerTag"), &GamerTag, Serializer);		
}

void UGamerTagAssociation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("projectId")), ProjectId, OuterOwner);
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("gamerTag")), GamerTag, OuterOwner);
}



