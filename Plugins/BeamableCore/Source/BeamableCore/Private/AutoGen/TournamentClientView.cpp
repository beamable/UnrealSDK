
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
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	StartTimeUtc = Bag->GetStringField(TEXT("startTimeUtc"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("secondsRemaining")), SecondsRemaining);
	Cycle = Bag->GetIntegerField(TEXT("cycle"));
	EndTimeUtc = Bag->GetStringField(TEXT("endTimeUtc"));
	ContentId = Bag->GetStringField(TEXT("contentId"));
}



