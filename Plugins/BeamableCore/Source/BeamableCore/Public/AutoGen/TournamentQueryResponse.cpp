
#include "AutoGen/TournamentQueryResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UTournamentQueryResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentClientView*>(TEXT("tournaments"), Tournaments, Serializer);
}

void UTournamentQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentClientView*>(TEXT("tournaments"), Tournaments, Serializer);		
}

void UTournamentQueryResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UTournamentClientView*>(Bag->GetArrayField(TEXT("tournaments")), Tournaments, OuterOwner);
}