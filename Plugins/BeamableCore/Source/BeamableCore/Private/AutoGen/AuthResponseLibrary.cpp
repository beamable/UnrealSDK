
#include "BeamableCore/Public/AutoGen/AuthResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthResponseLibrary::AuthResponseToJsonString(const UAuthResponse* Serializable, const bool Pretty)
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

UAuthResponse* UAuthResponseLibrary::Make(FOptionalString AccessToken, FOptionalString RefreshToken, UObject* Outer)
{
	auto Serializable = NewObject<UAuthResponse>(Outer);
	Serializable->AccessToken = AccessToken;
	Serializable->RefreshToken = RefreshToken;
	
	return Serializable;
}

void UAuthResponseLibrary::Break(const UAuthResponse* Serializable, FOptionalString& AccessToken, FOptionalString& RefreshToken)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AccessToken = Serializable->AccessToken;
		RefreshToken = Serializable->RefreshToken;
	}
		
}

