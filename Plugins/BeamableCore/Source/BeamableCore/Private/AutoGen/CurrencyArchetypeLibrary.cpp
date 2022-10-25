
#include "AutoGen/CurrencyArchetypeLibrary.h"

#include "CoreMinimal.h"


FString UCurrencyArchetypeLibrary::CurrencyArchetypeToJsonString(const UCurrencyArchetype* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UCurrencyArchetype* UCurrencyArchetypeLibrary::Make(FString Symbol, FOptionalInventoryProxySettings Proxy, FOptionalClientPermission ClientPermission, FOptionalInt64 StartingAmount, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyArchetype>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Proxy = Proxy;
	Serializable->ClientPermission = ClientPermission;
	Serializable->StartingAmount = StartingAmount;
	
	return Serializable;
}

void UCurrencyArchetypeLibrary::Break(const UCurrencyArchetype* Serializable, FString& Symbol, FOptionalInventoryProxySettings& Proxy, FOptionalClientPermission& ClientPermission, FOptionalInt64& StartingAmount)
{
	Symbol = Serializable->Symbol;
	Proxy = Serializable->Proxy;
	ClientPermission = Serializable->ClientPermission;
	StartingAmount = Serializable->StartingAmount;
		
}

