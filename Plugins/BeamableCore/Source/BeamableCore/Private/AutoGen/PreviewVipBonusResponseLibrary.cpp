
#include "BeamableCore/Public/AutoGen/PreviewVipBonusResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPreviewVipBonusResponseLibrary::PreviewVipBonusResponseToJsonString(const UPreviewVipBonusResponse* Serializable, const bool Pretty)
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

UPreviewVipBonusResponse* UPreviewVipBonusResponseLibrary::Make(TArray<UCurrencyPreview*> Currencies, UObject* Outer)
{
	auto Serializable = NewObject<UPreviewVipBonusResponse>(Outer);
	Serializable->Currencies = Currencies;
	
	return Serializable;
}

void UPreviewVipBonusResponseLibrary::Break(const UPreviewVipBonusResponse* Serializable, TArray<UCurrencyPreview*>& Currencies)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Currencies = Serializable->Currencies;
	}
		
}

