
#include "BeamableCore/Public/AutoGen/GetTransactionsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetTransactionsResponseLibrary::GetTransactionsResponseToJsonString(const UGetTransactionsResponse* Serializable, const bool Pretty)
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

UGetTransactionsResponse* UGetTransactionsResponseLibrary::Make(FOptionalArrayOfTransaction Transactions, UObject* Outer)
{
	auto Serializable = NewObject<UGetTransactionsResponse>(Outer);
	Serializable->Transactions = Transactions;
	
	return Serializable;
}

void UGetTransactionsResponseLibrary::Break(const UGetTransactionsResponse* Serializable, FOptionalArrayOfTransaction& Transactions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Transactions = Serializable->Transactions;
	}
		
}

