
#include "BeamableCore/Public/AutoGen/SessionHistoryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionHistoryResponseLibrary::SessionHistoryResponseToJsonString(const USessionHistoryResponse* Serializable, const bool Pretty)
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

USessionHistoryResponse* USessionHistoryResponseLibrary::Make(ULocalDate* Date, int32 DaysPlayed, TArray<FString> Payments, TArray<UPaymentTotal*> TotalPaid, TArray<FString> Sessions, FOptionalString InstallDate, UObject* Outer)
{
	auto Serializable = NewObject<USessionHistoryResponse>(Outer);
	Serializable->Date = Date;
	Serializable->DaysPlayed = DaysPlayed;
	Serializable->Payments = Payments;
	Serializable->TotalPaid = TotalPaid;
	Serializable->Sessions = Sessions;
	Serializable->InstallDate = InstallDate;
	
	return Serializable;
}

void USessionHistoryResponseLibrary::Break(const USessionHistoryResponse* Serializable, ULocalDate*& Date, int32& DaysPlayed, TArray<FString>& Payments, TArray<UPaymentTotal*>& TotalPaid, TArray<FString>& Sessions, FOptionalString& InstallDate)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Date = Serializable->Date;
		DaysPlayed = Serializable->DaysPlayed;
		Payments = Serializable->Payments;
		TotalPaid = Serializable->TotalPaid;
		Sessions = Serializable->Sessions;
		InstallDate = Serializable->InstallDate;
	}
		
}

