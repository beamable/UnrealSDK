
#include "BeamableCore/Public/AutoGen/GetGroupsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetGroupsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetGroupsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentGroupEntry*>(TEXT("entries"), Entries, Serializer);
	UBeamJsonUtils::SerializeOptional<UTournamentGroupEntry*>(TEXT("focus"), &Focus, Serializer);
}

void UGetGroupsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentGroupEntry*>(TEXT("entries"), Entries, Serializer);
	UBeamJsonUtils::SerializeOptional<UTournamentGroupEntry*>(TEXT("focus"), &Focus, Serializer);		
}

void UGetGroupsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UTournamentGroupEntry*>(Bag->GetArrayField(TEXT("entries")), Entries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UTournamentGroupEntry*>("focus", Bag, Focus, OuterOwner);
}



