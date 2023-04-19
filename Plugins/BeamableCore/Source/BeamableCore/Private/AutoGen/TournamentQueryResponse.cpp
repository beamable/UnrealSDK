
#include "BeamableCore/Public/AutoGen/TournamentQueryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UTournamentQueryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UTournamentQueryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentClientView*>(TEXT("tournaments"), Tournaments, Serializer);
}

void UTournamentQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentClientView*>(TEXT("tournaments"), Tournaments, Serializer);		
}

void UTournamentQueryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UTournamentClientView*>(Bag->GetArrayField(TEXT("tournaments")), Tournaments, OuterOwner);
}



