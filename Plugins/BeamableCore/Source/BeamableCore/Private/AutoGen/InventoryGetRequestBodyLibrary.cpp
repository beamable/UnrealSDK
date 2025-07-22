
#include "BeamableCore/Public/AutoGen/InventoryGetRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInventoryGetRequestBodyLibrary::InventoryGetRequestBodyToJsonString(const UInventoryGetRequestBody* Serializable, const bool Pretty)
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

UInventoryGetRequestBody* UInventoryGetRequestBodyLibrary::Make(FOptionalString Scope, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryGetRequestBody>(Outer);
	Serializable->Scope = Scope;
	
	return Serializable;
}

void UInventoryGetRequestBodyLibrary::Break(const UInventoryGetRequestBody* Serializable, FOptionalString& Scope)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Scope = Serializable->Scope;
	}
		
}

