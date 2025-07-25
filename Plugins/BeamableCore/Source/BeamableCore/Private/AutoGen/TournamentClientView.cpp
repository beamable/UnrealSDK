
#include "BeamableCore/Public/AutoGen/TournamentClientView.h"

#include "Misc/DefaultValueHelper.h"


void UTournamentClientView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UTournamentClientView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("startTimeUtc"), StartTimeUtc, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("secondsRemaining"), SecondsRemaining, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cycle"), Cycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endTimeUtc"), EndTimeUtc, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
}

void UTournamentClientView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("startTimeUtc"), StartTimeUtc, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("secondsRemaining"), SecondsRemaining, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cycle"), Cycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endTimeUtc"), EndTimeUtc, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);		
}

void UTournamentClientView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tournamentId"), Bag, TournamentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("startTimeUtc"), Bag, StartTimeUtc);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("secondsRemaining"), Bag, SecondsRemaining);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("cycle"), Bag, Cycle);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("endTimeUtc"), Bag, EndTimeUtc);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
}



