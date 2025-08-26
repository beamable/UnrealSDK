
#include "BeamableCore/Public/AutoGen/AccountSearchResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountSearchResponseLibrary::AccountSearchResponseToJsonString(const UAccountSearchResponse* Serializable, const bool Pretty)
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

UAccountSearchResponse* UAccountSearchResponseLibrary::Make(TArray<UAccountsBasicAccount*> Accounts, UObject* Outer)
{
	auto Serializable = NewObject<UAccountSearchResponse>(Outer);
	Serializable->Accounts = Accounts;
	
	return Serializable;
}

void UAccountSearchResponseLibrary::Break(const UAccountSearchResponse* Serializable, TArray<UAccountsBasicAccount*>& Accounts)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Accounts = Serializable->Accounts;
	}
		
}

