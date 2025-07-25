
#include "BeamableCore/Public/AutoGen/VipBonusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UVipBonusLibrary::VipBonusToJsonString(const UVipBonus* Serializable, const bool Pretty)
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

UVipBonus* UVipBonusLibrary::Make(FString Currency, double Multiplier, int32 RoundToNearest, UObject* Outer)
{
	auto Serializable = NewObject<UVipBonus>(Outer);
	Serializable->Currency = Currency;
	Serializable->Multiplier = Multiplier;
	Serializable->RoundToNearest = RoundToNearest;
	
	return Serializable;
}

void UVipBonusLibrary::Break(const UVipBonus* Serializable, FString& Currency, double& Multiplier, int32& RoundToNearest)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Currency = Serializable->Currency;
		Multiplier = Serializable->Multiplier;
		RoundToNearest = Serializable->RoundToNearest;
	}
		
}

