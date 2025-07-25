
#include "BeamableCore/Public/AutoGen/PriceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPriceLibrary::PriceToJsonString(const UPrice* Serializable, const bool Pretty)
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

UPrice* UPriceLibrary::Make(FString Type, FString Symbol, FOptionalInt32 Amount, FOptionalArrayOfInt32 Schedule, UObject* Outer)
{
	auto Serializable = NewObject<UPrice>(Outer);
	Serializable->Type = Type;
	Serializable->Symbol = Symbol;
	Serializable->Amount = Amount;
	Serializable->Schedule = Schedule;
	
	return Serializable;
}

void UPriceLibrary::Break(const UPrice* Serializable, FString& Type, FString& Symbol, FOptionalInt32& Amount, FOptionalArrayOfInt32& Schedule)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Type = Serializable->Type;
		Symbol = Serializable->Symbol;
		Amount = Serializable->Amount;
		Schedule = Serializable->Schedule;
	}
		
}

