
#include "AutoGen/ItemArchetypeLibrary.h"

#include "CoreMinimal.h"


FString UItemArchetypeLibrary::ItemArchetypeToJsonString(const UItemArchetype* Serializable, const bool Pretty)
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

UItemArchetype* UItemArchetypeLibrary::Make(FString Symbol, FOptionalInventoryProxySettings Proxy, FOptionalClientPermission ClientPermission, UObject* Outer)
{
	auto Serializable = NewObject<UItemArchetype>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Proxy = Proxy;
	Serializable->ClientPermission = ClientPermission;
	
	return Serializable;
}

void UItemArchetypeLibrary::Break(const UItemArchetype* Serializable, FString& Symbol, FOptionalInventoryProxySettings& Proxy, FOptionalClientPermission& ClientPermission)
{
	Symbol = Serializable->Symbol;
	Proxy = Serializable->Proxy;
	ClientPermission = Serializable->ClientPermission;
		
}

