
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionClientHistoryResponseLibrary::SessionClientHistoryResponseToJsonString(const USessionClientHistoryResponse* Serializable, const bool Pretty)
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

USessionClientHistoryResponse* USessionClientHistoryResponseLibrary::Make(ULocalDate* Date, int32 DaysPlayed, TArray<FString> Sessions, FOptionalString InstallDate, UObject* Outer)
{
	auto Serializable = NewObject<USessionClientHistoryResponse>(Outer);
	Serializable->Date = Date;
	Serializable->DaysPlayed = DaysPlayed;
	Serializable->Sessions = Sessions;
	Serializable->InstallDate = InstallDate;
	
	return Serializable;
}

void USessionClientHistoryResponseLibrary::Break(const USessionClientHistoryResponse* Serializable, ULocalDate*& Date, int32& DaysPlayed, TArray<FString>& Sessions, FOptionalString& InstallDate)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Date = Serializable->Date;
		DaysPlayed = Serializable->DaysPlayed;
		Sessions = Serializable->Sessions;
		InstallDate = Serializable->InstallDate;
	}
		
}

