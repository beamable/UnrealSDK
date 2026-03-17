
#include "BeamableCore/Public/AutoGen/AuthV2ListTokensResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2ListTokensResponseLibrary::AuthV2ListTokensResponseToJsonString(const UAuthV2ListTokensResponse* Serializable, const bool Pretty)
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

UAuthV2ListTokensResponse* UAuthV2ListTokensResponseLibrary::Make(FOptionalArrayOfAuthV2RefreshTokenResponse Tokens, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2ListTokensResponse>(Outer);
	Serializable->Tokens = Tokens;
	
	return Serializable;
}

void UAuthV2ListTokensResponseLibrary::Break(const UAuthV2ListTokensResponse* Serializable, FOptionalArrayOfAuthV2RefreshTokenResponse& Tokens)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Tokens = Serializable->Tokens;
	}
		
}

