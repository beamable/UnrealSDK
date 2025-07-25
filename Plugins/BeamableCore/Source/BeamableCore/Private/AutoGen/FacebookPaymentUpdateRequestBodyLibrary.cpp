
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFacebookPaymentUpdateRequestBodyLibrary::FacebookPaymentUpdateRequestBodyToJsonString(const UFacebookPaymentUpdateRequestBody* Serializable, const bool Pretty)
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

UFacebookPaymentUpdateRequestBody* UFacebookPaymentUpdateRequestBodyLibrary::Make(FString Object, TArray<UFacebookUpdatedEntry*> Entry, UObject* Outer)
{
	auto Serializable = NewObject<UFacebookPaymentUpdateRequestBody>(Outer);
	Serializable->Object = Object;
	Serializable->Entry = Entry;
	
	return Serializable;
}

void UFacebookPaymentUpdateRequestBodyLibrary::Break(const UFacebookPaymentUpdateRequestBody* Serializable, FString& Object, TArray<UFacebookUpdatedEntry*>& Entry)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Object = Serializable->Object;
		Entry = Serializable->Entry;
	}
		
}

