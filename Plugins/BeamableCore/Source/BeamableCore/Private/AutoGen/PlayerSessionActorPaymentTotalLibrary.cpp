
#include "BeamableCore/Public/AutoGen/PlayerSessionActorPaymentTotalLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerSessionActorPaymentTotalLibrary::PlayerSessionActorPaymentTotalToJsonString(const UPlayerSessionActorPaymentTotal* Serializable, const bool Pretty)
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

UPlayerSessionActorPaymentTotal* UPlayerSessionActorPaymentTotalLibrary::Make(FOptionalString Currency, FOptionalInt64 Amount, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerSessionActorPaymentTotal>(Outer);
	Serializable->Currency = Currency;
	Serializable->Amount = Amount;
	
	return Serializable;
}

void UPlayerSessionActorPaymentTotalLibrary::Break(const UPlayerSessionActorPaymentTotal* Serializable, FOptionalString& Currency, FOptionalInt64& Amount)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Currency = Serializable->Currency;
		Amount = Serializable->Amount;
	}
		
}

