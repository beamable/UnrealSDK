
#include "BeamableCore/Public/AutoGen/CurrencyArchetypeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyArchetypeLibrary::CurrencyArchetypeToJsonString(const UCurrencyArchetype* Serializable, const bool Pretty)
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

UCurrencyArchetype* UCurrencyArchetypeLibrary::Make(FString Symbol, FOptionalFederationInfo External, FOptionalBeamClientPermission ClientPermission, FOptionalInt64 StartingAmount, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyArchetype>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->External = External;
	Serializable->ClientPermission = ClientPermission;
	Serializable->StartingAmount = StartingAmount;
	
	return Serializable;
}

void UCurrencyArchetypeLibrary::Break(const UCurrencyArchetype* Serializable, FString& Symbol, FOptionalFederationInfo& External, FOptionalBeamClientPermission& ClientPermission, FOptionalInt64& StartingAmount)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		External = Serializable->External;
		ClientPermission = Serializable->ClientPermission;
		StartingAmount = Serializable->StartingAmount;
	}
		
}

