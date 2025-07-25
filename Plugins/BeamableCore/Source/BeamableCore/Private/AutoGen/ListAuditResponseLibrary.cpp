
#include "BeamableCore/Public/AutoGen/ListAuditResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListAuditResponseLibrary::ListAuditResponseToJsonString(const UListAuditResponse* Serializable, const bool Pretty)
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

UListAuditResponse* UListAuditResponseLibrary::Make(TArray<UPaymentAuditEntryViewModel*> Audits, UObject* Outer)
{
	auto Serializable = NewObject<UListAuditResponse>(Outer);
	Serializable->Audits = Audits;
	
	return Serializable;
}

void UListAuditResponseLibrary::Break(const UListAuditResponse* Serializable, TArray<UPaymentAuditEntryViewModel*>& Audits)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Audits = Serializable->Audits;
	}
		
}

