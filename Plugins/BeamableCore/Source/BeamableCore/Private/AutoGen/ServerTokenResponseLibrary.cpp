
#include "BeamableCore/Public/AutoGen/ServerTokenResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServerTokenResponseLibrary::ServerTokenResponseToJsonString(const UServerTokenResponse* Serializable, const bool Pretty)
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

UServerTokenResponse* UServerTokenResponseLibrary::Make(FOptionalString AccessToken, UObject* Outer)
{
	auto Serializable = NewObject<UServerTokenResponse>(Outer);
	Serializable->AccessToken = AccessToken;
	
	return Serializable;
}

void UServerTokenResponseLibrary::Break(const UServerTokenResponse* Serializable, FOptionalString& AccessToken)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AccessToken = Serializable->AccessToken;
	}
		
}

