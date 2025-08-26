
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFacebookPaymentUpdateResponseLibrary::FacebookPaymentUpdateResponseToJsonString(const UFacebookPaymentUpdateResponse* Serializable, const bool Pretty)
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

UFacebookPaymentUpdateResponse* UFacebookPaymentUpdateResponseLibrary::Make(FString Result, UObject* Outer)
{
	auto Serializable = NewObject<UFacebookPaymentUpdateResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void UFacebookPaymentUpdateResponseLibrary::Break(const UFacebookPaymentUpdateResponse* Serializable, FString& Result)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
	}
		
}

