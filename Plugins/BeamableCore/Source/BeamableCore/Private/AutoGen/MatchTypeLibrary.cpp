
#include "BeamableCore/Public/AutoGen/MatchTypeLibrary.h"

#include "CoreMinimal.h"


FString UMatchTypeLibrary::MatchTypeToJsonString(const UMatchType* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UMatchType* UMatchTypeLibrary::Make(FOptionalBeamContentId Id, FOptionalInt32 WaitAfterMinReachedSecs, FOptionalInt32 MaxWaitDurationSecs, FOptionalInt32 MatchingIntervalSecs, FOptionalArrayOfTeamContentProto Teams, UObject* Outer)
{
	auto Serializable = NewObject<UMatchType>(Outer);
	Serializable->Id = Id;
	Serializable->WaitAfterMinReachedSecs = WaitAfterMinReachedSecs;
	Serializable->MaxWaitDurationSecs = MaxWaitDurationSecs;
	Serializable->MatchingIntervalSecs = MatchingIntervalSecs;
	Serializable->Teams = Teams;
	
	return Serializable;
}

void UMatchTypeLibrary::Break(const UMatchType* Serializable, FOptionalBeamContentId& Id, FOptionalInt32& WaitAfterMinReachedSecs, FOptionalInt32& MaxWaitDurationSecs, FOptionalInt32& MatchingIntervalSecs, FOptionalArrayOfTeamContentProto& Teams)
{
	Id = Serializable->Id;
	WaitAfterMinReachedSecs = Serializable->WaitAfterMinReachedSecs;
	MaxWaitDurationSecs = Serializable->MaxWaitDurationSecs;
	MatchingIntervalSecs = Serializable->MatchingIntervalSecs;
	Teams = Serializable->Teams;
		
}

