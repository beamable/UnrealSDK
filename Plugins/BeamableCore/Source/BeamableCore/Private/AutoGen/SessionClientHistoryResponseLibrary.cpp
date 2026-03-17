
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

USessionClientHistoryResponse* USessionClientHistoryResponseLibrary::Make(FOptionalString Date, FOptionalString InstallDate, FOptionalInt32 DaysPlayed, FOptionalArrayOfString Sessions, UObject* Outer)
{
	auto Serializable = NewObject<USessionClientHistoryResponse>(Outer);
	Serializable->Date = Date;
	Serializable->InstallDate = InstallDate;
	Serializable->DaysPlayed = DaysPlayed;
	Serializable->Sessions = Sessions;
	
	return Serializable;
}

void USessionClientHistoryResponseLibrary::Break(const USessionClientHistoryResponse* Serializable, FOptionalString& Date, FOptionalString& InstallDate, FOptionalInt32& DaysPlayed, FOptionalArrayOfString& Sessions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Date = Serializable->Date;
		InstallDate = Serializable->InstallDate;
		DaysPlayed = Serializable->DaysPlayed;
		Sessions = Serializable->Sessions;
	}
		
}

