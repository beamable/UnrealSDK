
#include "BeamableCore/Public/AutoGen/CreateDonationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateDonationRequestBodyLibrary::CreateDonationRequestBodyToJsonString(const UCreateDonationRequestBody* Serializable, const bool Pretty)
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

UCreateDonationRequestBody* UCreateDonationRequestBodyLibrary::Make(FString CurrencyId, int64 Amount, FOptionalString Config, UObject* Outer)
{
	auto Serializable = NewObject<UCreateDonationRequestBody>(Outer);
	Serializable->CurrencyId = CurrencyId;
	Serializable->Amount = Amount;
	Serializable->Config = Config;
	
	return Serializable;
}

void UCreateDonationRequestBodyLibrary::Break(const UCreateDonationRequestBody* Serializable, FString& CurrencyId, int64& Amount, FOptionalString& Config)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		CurrencyId = Serializable->CurrencyId;
		Amount = Serializable->Amount;
		Config = Serializable->Config;
	}
		
}

