
#include "BeamableCore/Public/AutoGen/AuthV2ServerTokenResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2ServerTokenResponseLibrary::AuthV2ServerTokenResponseToJsonString(const UAuthV2ServerTokenResponse* Serializable, const bool Pretty)
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

UAuthV2ServerTokenResponse* UAuthV2ServerTokenResponseLibrary::Make(FOptionalString AccessToken, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2ServerTokenResponse>(Outer);
	Serializable->AccessToken = AccessToken;
	
	return Serializable;
}

void UAuthV2ServerTokenResponseLibrary::Break(const UAuthV2ServerTokenResponse* Serializable, FOptionalString& AccessToken)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AccessToken = Serializable->AccessToken;
	}
		
}

