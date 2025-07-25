
#include "BeamableCore/Public/AutoGen/InventoryQueryRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInventoryQueryRequestBodyLibrary::InventoryQueryRequestBodyToJsonString(const UInventoryQueryRequestBody* Serializable, const bool Pretty)
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

UInventoryQueryRequestBody* UInventoryQueryRequestBodyLibrary::Make(FOptionalArrayOfString Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryQueryRequestBody>(Outer);
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UInventoryQueryRequestBodyLibrary::Break(const UInventoryQueryRequestBody* Serializable, FOptionalArrayOfString& Scopes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Scopes = Serializable->Scopes;
	}
		
}

