
#include "BeamableCore/Public/AutoGen/SubscriptionVerificationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USubscriptionVerificationRequestBodyLibrary::SubscriptionVerificationRequestBodyToJsonString(const USubscriptionVerificationRequestBody* Serializable, const bool Pretty)
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

USubscriptionVerificationRequestBody* USubscriptionVerificationRequestBodyLibrary::Make(FString HubMode, FString HubChallenge, FString HubVerifyToken, UObject* Outer)
{
	auto Serializable = NewObject<USubscriptionVerificationRequestBody>(Outer);
	Serializable->HubMode = HubMode;
	Serializable->HubChallenge = HubChallenge;
	Serializable->HubVerifyToken = HubVerifyToken;
	
	return Serializable;
}

void USubscriptionVerificationRequestBodyLibrary::Break(const USubscriptionVerificationRequestBody* Serializable, FString& HubMode, FString& HubChallenge, FString& HubVerifyToken)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		HubMode = Serializable->HubMode;
		HubChallenge = Serializable->HubChallenge;
		HubVerifyToken = Serializable->HubVerifyToken;
	}
		
}

