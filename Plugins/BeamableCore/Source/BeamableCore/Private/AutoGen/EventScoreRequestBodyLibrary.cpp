
#include "BeamableCore/Public/AutoGen/EventScoreRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventScoreRequestBodyLibrary::EventScoreRequestBodyToJsonString(const UEventScoreRequestBody* Serializable, const bool Pretty)
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

UEventScoreRequestBody* UEventScoreRequestBodyLibrary::Make(FString EventId, double Score, FOptionalBool bIncrement, FOptionalMapOfString Stats, UObject* Outer)
{
	auto Serializable = NewObject<UEventScoreRequestBody>(Outer);
	Serializable->EventId = EventId;
	Serializable->Score = Score;
	Serializable->bIncrement = bIncrement;
	Serializable->Stats = Stats;
	
	return Serializable;
}

void UEventScoreRequestBodyLibrary::Break(const UEventScoreRequestBody* Serializable, FString& EventId, double& Score, FOptionalBool& bIncrement, FOptionalMapOfString& Stats)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		EventId = Serializable->EventId;
		Score = Serializable->Score;
		bIncrement = Serializable->bIncrement;
		Stats = Serializable->Stats;
	}
		
}

