
#include "AutoGen/InventoryProxySettingsLibrary.h"

#include "CoreMinimal.h"


FString UInventoryProxySettingsLibrary::InventoryProxySettingsToJsonString(const UInventoryProxySettings* Serializable, const bool Pretty)
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

UInventoryProxySettings* UInventoryProxySettingsLibrary::Make(FString Service, FOptionalString Namespace, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryProxySettings>(Outer);
	Serializable->Service = Service;
	Serializable->Namespace = Namespace;
	
	return Serializable;
}

void UInventoryProxySettingsLibrary::Break(const UInventoryProxySettings* Serializable, FString& Service, FOptionalString& Namespace)
{
	Service = Serializable->Service;
	Namespace = Serializable->Namespace;
		
}

