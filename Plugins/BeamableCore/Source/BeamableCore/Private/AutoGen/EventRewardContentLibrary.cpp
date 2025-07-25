
#include "BeamableCore/Public/AutoGen/EventRewardContentLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventRewardContentLibrary::EventRewardContentToJsonString(const UEventRewardContent* Serializable, const bool Pretty)
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

UEventRewardContent* UEventRewardContentLibrary::Make(double Min, FOptionalDouble Max, FOptionalArrayOfEventInventoryRewardCurrency Currencies, FOptionalArrayOfEventInventoryRewardItem Items, FOptionalArrayOfEventRewardObtain Obtain, UObject* Outer)
{
	auto Serializable = NewObject<UEventRewardContent>(Outer);
	Serializable->Min = Min;
	Serializable->Max = Max;
	Serializable->Currencies = Currencies;
	Serializable->Items = Items;
	Serializable->Obtain = Obtain;
	
	return Serializable;
}

void UEventRewardContentLibrary::Break(const UEventRewardContent* Serializable, double& Min, FOptionalDouble& Max, FOptionalArrayOfEventInventoryRewardCurrency& Currencies, FOptionalArrayOfEventInventoryRewardItem& Items, FOptionalArrayOfEventRewardObtain& Obtain)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Min = Serializable->Min;
		Max = Serializable->Max;
		Currencies = Serializable->Currencies;
		Items = Serializable->Items;
		Obtain = Serializable->Obtain;
	}
		
}

