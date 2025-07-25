
#include "BeamableCore/Public/AutoGen/GetGroupsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGroupsRequestBodyLibrary::GetGroupsRequestBodyToJsonString(const UGetGroupsRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UGetGroupsRequestBody* UGetGroupsRequestBodyLibrary::Make(FString TournamentId, FOptionalInt32 Max, FOptionalInt64 Focus, FOptionalInt32 Cycle, FOptionalInt32 From, FOptionalString ContentId, UObject* Outer)
{
	auto Serializable = NewObject<UGetGroupsRequestBody>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->Max = Max;
	Serializable->Focus = Focus;
	Serializable->Cycle = Cycle;
	Serializable->From = From;
	Serializable->ContentId = ContentId;
	
	return Serializable;
}

void UGetGroupsRequestBodyLibrary::Break(const UGetGroupsRequestBody* Serializable, FString& TournamentId, FOptionalInt32& Max, FOptionalInt64& Focus, FOptionalInt32& Cycle, FOptionalInt32& From, FOptionalString& ContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TournamentId = Serializable->TournamentId;
		Max = Serializable->Max;
		Focus = Serializable->Focus;
		Cycle = Serializable->Cycle;
		From = Serializable->From;
		ContentId = Serializable->ContentId;
	}
		
}

