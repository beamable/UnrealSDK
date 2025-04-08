
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveEntryRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardRemoveEntryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
}

void ULeaderboardRemoveEntryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);		
}

void ULeaderboardRemoveEntryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
}



