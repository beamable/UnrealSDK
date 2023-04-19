
#include "BeamableCore/Public/AutoGen/LeaderboardPlayerRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardPlayerRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("dbid"), Dbid);
}

void ULeaderboardPlayerRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("dbid"), Dbid);		
}

void ULeaderboardPlayerRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("dbid")), Dbid);
}



