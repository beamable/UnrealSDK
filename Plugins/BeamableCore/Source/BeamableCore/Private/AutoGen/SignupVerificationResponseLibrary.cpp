
#include "BeamableCore/Public/AutoGen/SignupVerificationResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USignupVerificationResponseLibrary::SignupVerificationResponseToJsonString(const USignupVerificationResponse* Serializable, const bool Pretty)
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

USignupVerificationResponse* USignupVerificationResponseLibrary::Make(UAccountPlayerView* Account, UTokenResponse* Token, UObject* Outer)
{
	auto Serializable = NewObject<USignupVerificationResponse>(Outer);
	Serializable->Account = Account;
	Serializable->Token = Token;
	
	return Serializable;
}

void USignupVerificationResponseLibrary::Break(const USignupVerificationResponse* Serializable, UAccountPlayerView*& Account, UTokenResponse*& Token)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Account = Serializable->Account;
		Token = Serializable->Token;
	}
		
}

