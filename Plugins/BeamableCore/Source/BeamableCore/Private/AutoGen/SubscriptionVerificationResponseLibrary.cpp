
#include "BeamableCore/Public/AutoGen/SubscriptionVerificationResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USubscriptionVerificationResponseLibrary::SubscriptionVerificationResponseToJsonString(const USubscriptionVerificationResponse* Serializable, const bool Pretty)
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

USubscriptionVerificationResponse* USubscriptionVerificationResponseLibrary::Make(FString HubChallenge, UObject* Outer)
{
	auto Serializable = NewObject<USubscriptionVerificationResponse>(Outer);
	Serializable->HubChallenge = HubChallenge;
	
	return Serializable;
}

void USubscriptionVerificationResponseLibrary::Break(const USubscriptionVerificationResponse* Serializable, FString& HubChallenge)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		HubChallenge = Serializable->HubChallenge;
	}
		
}

