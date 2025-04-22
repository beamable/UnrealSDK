
#include "BeamableCore/Public/AutoGen/LeaderboardPlayerRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardPlayerRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dbid"), Dbid, Serializer);
}

void ULeaderboardPlayerRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dbid"), Dbid, Serializer);		
}

void ULeaderboardPlayerRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("dbid")), Dbid);
}



