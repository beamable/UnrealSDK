
#include "BeamableCore/Public/AutoGen/TransactionLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTransactionLibrary::TransactionToJsonString(const UTransaction* Serializable, const bool Pretty)
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

UTransaction* UTransactionLibrary::Make(int64 PlayerId, int64 TransactionId, FString ProviderName, UTransactionDetails* Details, FOptionalBool bIsInTerminalState, FOptionalTransactionState State, FOptionalString ProviderId, FOptionalDateTime Created, FOptionalDateTime Updated, FOptionalString Version, FOptionalString ReplayGuardValue, FOptionalArrayOfTransactionHistoryEntry History, UObject* Outer)
{
	auto Serializable = NewObject<UTransaction>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->TransactionId = TransactionId;
	Serializable->ProviderName = ProviderName;
	Serializable->Details = Details;
	Serializable->bIsInTerminalState = bIsInTerminalState;
	Serializable->State = State;
	Serializable->ProviderId = ProviderId;
	Serializable->Created = Created;
	Serializable->Updated = Updated;
	Serializable->Version = Version;
	Serializable->ReplayGuardValue = ReplayGuardValue;
	Serializable->History = History;
	
	return Serializable;
}

void UTransactionLibrary::Break(const UTransaction* Serializable, int64& PlayerId, int64& TransactionId, FString& ProviderName, UTransactionDetails*& Details, FOptionalBool& bIsInTerminalState, FOptionalTransactionState& State, FOptionalString& ProviderId, FOptionalDateTime& Created, FOptionalDateTime& Updated, FOptionalString& Version, FOptionalString& ReplayGuardValue, FOptionalArrayOfTransactionHistoryEntry& History)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		TransactionId = Serializable->TransactionId;
		ProviderName = Serializable->ProviderName;
		Details = Serializable->Details;
		bIsInTerminalState = Serializable->bIsInTerminalState;
		State = Serializable->State;
		ProviderId = Serializable->ProviderId;
		Created = Serializable->Created;
		Updated = Serializable->Updated;
		Version = Serializable->Version;
		ReplayGuardValue = Serializable->ReplayGuardValue;
		History = Serializable->History;
	}
		
}

