
#include "BeamableCore/Public/AutoGen/TransferRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTransferRequestBodyLibrary::TransferRequestBodyToJsonString(const UTransferRequestBody* Serializable, const bool Pretty)
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

UTransferRequestBody* UTransferRequestBodyLibrary::Make(FBeamGamerTag RecipientPlayer, FOptionalString Transaction, FOptionalMapOfInt64 Currencies, UObject* Outer)
{
	auto Serializable = NewObject<UTransferRequestBody>(Outer);
	Serializable->RecipientPlayer = RecipientPlayer;
	Serializable->Transaction = Transaction;
	Serializable->Currencies = Currencies;
	
	return Serializable;
}

void UTransferRequestBodyLibrary::Break(const UTransferRequestBody* Serializable, FBeamGamerTag& RecipientPlayer, FOptionalString& Transaction, FOptionalMapOfInt64& Currencies)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RecipientPlayer = Serializable->RecipientPlayer;
		Transaction = Serializable->Transaction;
		Currencies = Serializable->Currencies;
	}
		
}

