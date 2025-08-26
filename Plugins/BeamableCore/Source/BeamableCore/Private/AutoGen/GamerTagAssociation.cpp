
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
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("projectId"), Bag, ProjectId, OuterOwner);
	UBeamJsonUtils::DeserializeSemanticType<int64>(TEXT("gamerTag"), Bag, GamerTag, OuterOwner);
}



