
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

USessionHistoryResponse* USessionHistoryResponseLibrary::Make(FOptionalString Date, FOptionalString InstallDate, FOptionalInt32 DaysPlayed, FOptionalArrayOfString Sessions, FOptionalArrayOfString Payments, FOptionalArrayOfPlayerSessionActorPaymentTotal TotalPaid, UObject* Outer)
{
	auto Serializable = NewObject<USessionHistoryResponse>(Outer);
	Serializable->Date = Date;
	Serializable->InstallDate = InstallDate;
	Serializable->DaysPlayed = DaysPlayed;
	Serializable->Sessions = Sessions;
	Serializable->Payments = Payments;
	Serializable->TotalPaid = TotalPaid;
	
	return Serializable;
}

void USessionHistoryResponseLibrary::Break(const USessionHistoryResponse* Serializable, FOptionalString& Date, FOptionalString& InstallDate, FOptionalInt32& DaysPlayed, FOptionalArrayOfString& Sessions, FOptionalArrayOfString& Payments, FOptionalArrayOfPlayerSessionActorPaymentTotal& TotalPaid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Date = Serializable->Date;
		InstallDate = Serializable->InstallDate;
		DaysPlayed = Serializable->DaysPlayed;
		Sessions = Serializable->Sessions;
		Payments = Serializable->Payments;
		TotalPaid = Serializable->TotalPaid;
	}
		
}

