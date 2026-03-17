
#include "BeamableCore/Public/AutoGen/AuthV2RevokeRefreshTokensRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2RevokeRefreshTokensRequestBodyLibrary::AuthV2RevokeRefreshTokensRequestBodyToJsonString(const UAuthV2RevokeRefreshTokensRequestBody* Serializable, const bool Pretty)
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

UAuthV2RevokeRefreshTokensRequestBody* UAuthV2RevokeRefreshTokensRequestBodyLibrary::Make(TArray<FString> Tokens, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2RevokeRefreshTokensRequestBody>(Outer);
	Serializable->Tokens = Tokens;
	
	return Serializable;
}

void UAuthV2RevokeRefreshTokensRequestBodyLibrary::Break(const UAuthV2RevokeRefreshTokensRequestBody* Serializable, TArray<FString>& Tokens)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Tokens = Serializable->Tokens;
	}
		
}

