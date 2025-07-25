
#include "BeamableCore/Public/AutoGen/ThirdPartyAvailableRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UThirdPartyAvailableRequestBodyLibrary::ThirdPartyAvailableRequestBodyToJsonString(const UThirdPartyAvailableRequestBody* Serializable, const bool Pretty)
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

UThirdPartyAvailableRequestBody* UThirdPartyAvailableRequestBodyLibrary::Make(FString ThirdParty, FString Token, UObject* Outer)
{
	auto Serializable = NewObject<UThirdPartyAvailableRequestBody>(Outer);
	Serializable->ThirdParty = ThirdParty;
	Serializable->Token = Token;
	
	return Serializable;
}

void UThirdPartyAvailableRequestBodyLibrary::Break(const UThirdPartyAvailableRequestBody* Serializable, FString& ThirdParty, FString& Token)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ThirdParty = Serializable->ThirdParty;
		Token = Serializable->Token;
	}
		
}

