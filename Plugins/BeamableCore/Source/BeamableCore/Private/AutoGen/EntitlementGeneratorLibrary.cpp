
#include "BeamableCore/Public/AutoGen/EntitlementGeneratorLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEntitlementGeneratorLibrary::EntitlementGeneratorToJsonString(const UEntitlementGenerator* Serializable, const bool Pretty)
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

UEntitlementGenerator* UEntitlementGeneratorLibrary::Make(FString Symbol, FString Action, FOptionalInt32 Quantity, FOptionalEntitlementClaimWindow ClaimWindow, FOptionalString Specialization, FOptionalMapOfString Params, UObject* Outer)
{
	auto Serializable = NewObject<UEntitlementGenerator>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Action = Action;
	Serializable->Quantity = Quantity;
	Serializable->ClaimWindow = ClaimWindow;
	Serializable->Specialization = Specialization;
	Serializable->Params = Params;
	
	return Serializable;
}

void UEntitlementGeneratorLibrary::Break(const UEntitlementGenerator* Serializable, FString& Symbol, FString& Action, FOptionalInt32& Quantity, FOptionalEntitlementClaimWindow& ClaimWindow, FOptionalString& Specialization, FOptionalMapOfString& Params)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Action = Serializable->Action;
		Quantity = Serializable->Quantity;
		ClaimWindow = Serializable->ClaimWindow;
		Specialization = Serializable->Specialization;
		Params = Serializable->Params;
	}
		
}

