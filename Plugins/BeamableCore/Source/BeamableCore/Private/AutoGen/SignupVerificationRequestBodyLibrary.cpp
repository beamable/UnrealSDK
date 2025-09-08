
#include "BeamableCore/Public/AutoGen/SignupVerificationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USignupVerificationRequestBodyLibrary::SignupVerificationRequestBodyToJsonString(const USignupVerificationRequestBody* Serializable, const bool Pretty)
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

USignupVerificationRequestBody* USignupVerificationRequestBodyLibrary::Make(FString Email, FString Code, UObject* Outer)
{
	auto Serializable = NewObject<USignupVerificationRequestBody>(Outer);
	Serializable->Email = Email;
	Serializable->Code = Code;
	
	return Serializable;
}

void USignupVerificationRequestBodyLibrary::Break(const USignupVerificationRequestBody* Serializable, FString& Email, FString& Code)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Email = Serializable->Email;
		Code = Serializable->Code;
	}
		
}

