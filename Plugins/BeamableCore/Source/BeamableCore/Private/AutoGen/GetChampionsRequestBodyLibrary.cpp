
#include "BeamableCore/Public/AutoGen/GetChampionsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetChampionsRequestBodyLibrary::GetChampionsRequestBodyToJsonString(const UGetChampionsRequestBody* Serializable, const bool Pretty)
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

UGetChampionsRequestBody* UGetChampionsRequestBodyLibrary::Make(FString TournamentId, int32 Cycles, FOptionalString ContentId, UObject* Outer)
{
	auto Serializable = NewObject<UGetChampionsRequestBody>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->Cycles = Cycles;
	Serializable->ContentId = ContentId;
	
	return Serializable;
}

void UGetChampionsRequestBodyLibrary::Break(const UGetChampionsRequestBody* Serializable, FString& TournamentId, int32& Cycles, FOptionalString& ContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TournamentId = Serializable->TournamentId;
		Cycles = Serializable->Cycles;
		ContentId = Serializable->ContentId;
	}
		
}

