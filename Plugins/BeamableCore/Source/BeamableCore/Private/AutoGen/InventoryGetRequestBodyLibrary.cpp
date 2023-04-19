
#include "BeamableCore/Public/AutoGen/InventoryGetRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UInventoryGetRequestBodyLibrary::InventoryGetRequestBodyToJsonString(const UInventoryGetRequestBody* Serializable, const bool Pretty)
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

UInventoryGetRequestBody* UInventoryGetRequestBodyLibrary::Make(FOptionalString Scope, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryGetRequestBody>(Outer);
	Serializable->Scope = Scope;
	
	return Serializable;
}

void UInventoryGetRequestBodyLibrary::Break(const UInventoryGetRequestBody* Serializable, FOptionalString& Scope)
{
	Scope = Serializable->Scope;
		
}

