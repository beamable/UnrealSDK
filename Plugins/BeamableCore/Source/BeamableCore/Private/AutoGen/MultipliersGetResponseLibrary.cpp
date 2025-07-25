
#include "BeamableCore/Public/AutoGen/MultipliersGetResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMultipliersGetResponseLibrary::MultipliersGetResponseToJsonString(const UMultipliersGetResponse* Serializable, const bool Pretty)
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

UMultipliersGetResponse* UMultipliersGetResponseLibrary::Make(TArray<UVipBonus*> Multipliers, UObject* Outer)
{
	auto Serializable = NewObject<UMultipliersGetResponse>(Outer);
	Serializable->Multipliers = Multipliers;
	
	return Serializable;
}

void UMultipliersGetResponseLibrary::Break(const UMultipliersGetResponse* Serializable, TArray<UVipBonus*>& Multipliers)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Multipliers = Serializable->Multipliers;
	}
		
}

