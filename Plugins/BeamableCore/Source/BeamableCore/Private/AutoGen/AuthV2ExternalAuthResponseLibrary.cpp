
#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2ExternalAuthResponseLibrary::AuthV2ExternalAuthResponseToJsonString(const UAuthV2ExternalAuthResponse* Serializable, const bool Pretty)
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

UAuthV2ExternalAuthResponse* UAuthV2ExternalAuthResponseLibrary::Make(FOptionalBool bHasAccessToken, FOptionalBool bHasChallengeToken, FOptionalBool bHasExpiresInMs, FOptionalBool bHasRefreshToken, FOptionalString AccessToken, FOptionalString RefreshToken, FOptionalString ChallengeToken, FOptionalInt64 ExpiresInMs, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2ExternalAuthResponse>(Outer);
	Serializable->bHasAccessToken = bHasAccessToken;
	Serializable->bHasChallengeToken = bHasChallengeToken;
	Serializable->bHasExpiresInMs = bHasExpiresInMs;
	Serializable->bHasRefreshToken = bHasRefreshToken;
	Serializable->AccessToken = AccessToken;
	Serializable->RefreshToken = RefreshToken;
	Serializable->ChallengeToken = ChallengeToken;
	Serializable->ExpiresInMs = ExpiresInMs;
	
	return Serializable;
}

void UAuthV2ExternalAuthResponseLibrary::Break(const UAuthV2ExternalAuthResponse* Serializable, FOptionalBool& bHasAccessToken, FOptionalBool& bHasChallengeToken, FOptionalBool& bHasExpiresInMs, FOptionalBool& bHasRefreshToken, FOptionalString& AccessToken, FOptionalString& RefreshToken, FOptionalString& ChallengeToken, FOptionalInt64& ExpiresInMs)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bHasAccessToken = Serializable->bHasAccessToken;
		bHasChallengeToken = Serializable->bHasChallengeToken;
		bHasExpiresInMs = Serializable->bHasExpiresInMs;
		bHasRefreshToken = Serializable->bHasRefreshToken;
		AccessToken = Serializable->AccessToken;
		RefreshToken = Serializable->RefreshToken;
		ChallengeToken = Serializable->ChallengeToken;
		ExpiresInMs = Serializable->ExpiresInMs;
	}
		
}

