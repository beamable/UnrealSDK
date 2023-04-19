
#include "BeamableCore/Public/AutoGen/GetStandingsRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetStandingsRequestBodyLibrary::GetStandingsRequestBodyToJsonString(const UGetStandingsRequestBody* Serializable, const bool Pretty)
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

UGetStandingsRequestBody* UGetStandingsRequestBodyLibrary::Make(FString TournamentId, FOptionalInt32 Max, FOptionalInt64 Focus, FOptionalInt32 Cycle, FOptionalInt32 From, UObject* Outer)
{
	auto Serializable = NewObject<UGetStandingsRequestBody>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->Max = Max;
	Serializable->Focus = Focus;
	Serializable->Cycle = Cycle;
	Serializable->From = From;
	
	return Serializable;
}

void UGetStandingsRequestBodyLibrary::Break(const UGetStandingsRequestBody* Serializable, FString& TournamentId, FOptionalInt32& Max, FOptionalInt64& Focus, FOptionalInt32& Cycle, FOptionalInt32& From)
{
	TournamentId = Serializable->TournamentId;
	Max = Serializable->Max;
	Focus = Serializable->Focus;
	Cycle = Serializable->Cycle;
	From = Serializable->From;
		
}

