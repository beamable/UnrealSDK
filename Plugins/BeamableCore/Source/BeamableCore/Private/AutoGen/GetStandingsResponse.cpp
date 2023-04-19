
#include "BeamableCore/Public/AutoGen/GetStandingsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetStandingsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetStandingsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentEntry*>(TEXT("entries"), Entries, Serializer);
	UBeamJsonUtils::SerializeOptional<UTournamentEntry*>(TEXT("me"), &Me, Serializer);
}

void UGetStandingsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentEntry*>(TEXT("entries"), Entries, Serializer);
	UBeamJsonUtils::SerializeOptional<UTournamentEntry*>(TEXT("me"), &Me, Serializer);		
}

void UGetStandingsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UTournamentEntry*>(Bag->GetArrayField(TEXT("entries")), Entries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UTournamentEntry*>("me", Bag, Me, OuterOwner);
}



