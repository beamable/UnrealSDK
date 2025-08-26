
#include "BeamableCore/Public/AutoGen/ActivationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UActivationRequestBodyLibrary::ActivationRequestBodyToJsonString(const UActivationRequestBody* Serializable, const bool Pretty)
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

UActivationRequestBody* UActivationRequestBodyLibrary::Make(FString Token, int64 Cid, UObject* Outer)
{
	auto Serializable = NewObject<UActivationRequestBody>(Outer);
	Serializable->Token = Token;
	Serializable->Cid = Cid;
	
	return Serializable;
}

void UActivationRequestBodyLibrary::Break(const UActivationRequestBody* Serializable, FString& Token, int64& Cid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Token = Serializable->Token;
		Cid = Serializable->Cid;
	}
		
}

