
#include "BeamableCore/Public/AutoGen/AccountAvailableRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountAvailableRequestBodyLibrary::AccountAvailableRequestBodyToJsonString(const UAccountAvailableRequestBody* Serializable, const bool Pretty)
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

UAccountAvailableRequestBody* UAccountAvailableRequestBodyLibrary::Make(FString Email, UObject* Outer)
{
	auto Serializable = NewObject<UAccountAvailableRequestBody>(Outer);
	Serializable->Email = Email;
	
	return Serializable;
}

void UAccountAvailableRequestBodyLibrary::Break(const UAccountAvailableRequestBody* Serializable, FString& Email)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Email = Serializable->Email;
	}
		
}

