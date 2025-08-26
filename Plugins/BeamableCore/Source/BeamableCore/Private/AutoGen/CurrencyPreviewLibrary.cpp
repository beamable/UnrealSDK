
#include "BeamableCore/Public/AutoGen/CurrencyPreviewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyPreviewLibrary::CurrencyPreviewToJsonString(const UCurrencyPreview* Serializable, const bool Pretty)
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

UCurrencyPreview* UCurrencyPreviewLibrary::Make(FString Id, int64 Amount, int64 OriginalAmount, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyPreview>(Outer);
	Serializable->Id = Id;
	Serializable->Amount = Amount;
	Serializable->OriginalAmount = OriginalAmount;
	
	return Serializable;
}

void UCurrencyPreviewLibrary::Break(const UCurrencyPreview* Serializable, FString& Id, int64& Amount, int64& OriginalAmount)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Amount = Serializable->Amount;
		OriginalAmount = Serializable->OriginalAmount;
	}
		
}

