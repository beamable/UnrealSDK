
#include "BeamableCore/Public/AutoGen/TransactionHistoryEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTransactionHistoryEntryLibrary::TransactionHistoryEntryToJsonString(const UTransactionHistoryEntry* Serializable, const bool Pretty)
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

UTransactionHistoryEntry* UTransactionHistoryEntryLibrary::Make(EBeamTransactionState Change, FDateTime Timestamp, FOptionalString Data, UObject* Outer)
{
	auto Serializable = NewObject<UTransactionHistoryEntry>(Outer);
	Serializable->Change = Change;
	Serializable->Timestamp = Timestamp;
	Serializable->Data = Data;
	
	return Serializable;
}

void UTransactionHistoryEntryLibrary::Break(const UTransactionHistoryEntry* Serializable, EBeamTransactionState& Change, FDateTime& Timestamp, FOptionalString& Data)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Change = Serializable->Change;
		Timestamp = Serializable->Timestamp;
		Data = Serializable->Data;
	}
		
}

