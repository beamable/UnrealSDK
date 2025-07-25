
#include "BeamableCore/Public/AutoGen/TournamentQueryRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTournamentQueryRequestBodyLibrary::TournamentQueryRequestBodyToJsonString(const UTournamentQueryRequestBody* Serializable, const bool Pretty)
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

UTournamentQueryRequestBody* UTournamentQueryRequestBodyLibrary::Make(FOptionalBool bIsRunning, FOptionalString ContentId, FOptionalInt32 Cycle, UObject* Outer)
{
	auto Serializable = NewObject<UTournamentQueryRequestBody>(Outer);
	Serializable->bIsRunning = bIsRunning;
	Serializable->ContentId = ContentId;
	Serializable->Cycle = Cycle;
	
	return Serializable;
}

void UTournamentQueryRequestBodyLibrary::Break(const UTournamentQueryRequestBody* Serializable, FOptionalBool& bIsRunning, FOptionalString& ContentId, FOptionalInt32& Cycle)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsRunning = Serializable->bIsRunning;
		ContentId = Serializable->ContentId;
		Cycle = Serializable->Cycle;
	}
		
}

