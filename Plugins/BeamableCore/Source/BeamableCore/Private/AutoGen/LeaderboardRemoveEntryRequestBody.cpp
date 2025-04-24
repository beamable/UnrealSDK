
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveEntryRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardRemoveEntryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
}

void ULeaderboardRemoveEntryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);		
}

void ULeaderboardRemoveEntryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
}



