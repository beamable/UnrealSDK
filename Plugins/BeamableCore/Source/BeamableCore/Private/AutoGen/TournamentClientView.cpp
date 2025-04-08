
#include "BeamableCore/Public/AutoGen/TournamentClientView.h"

#include "Misc/DefaultValueHelper.h"


void UTournamentClientView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UTournamentClientView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("startTimeUtc"), StartTimeUtc);
	Serializer->WriteValue(TEXT("secondsRemaining"), SecondsRemaining);
	Serializer->WriteValue(TEXT("cycle"), Cycle);
	Serializer->WriteValue(TEXT("endTimeUtc"), EndTimeUtc);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
}

void UTournamentClientView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("startTimeUtc"), StartTimeUtc);
	Serializer->WriteValue(TEXT("secondsRemaining"), SecondsRemaining);
	Serializer->WriteValue(TEXT("cycle"), Cycle);
	Serializer->WriteValue(TEXT("endTimeUtc"), EndTimeUtc);
	Serializer->WriteValue(TEXT("contentId"), ContentId);		
}

void UTournamentClientView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("tournamentId")), TournamentId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("startTimeUtc")), StartTimeUtc);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("secondsRemaining")), SecondsRemaining);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cycle")), Cycle);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("endTimeUtc")), EndTimeUtc);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("contentId")), ContentId);
}



