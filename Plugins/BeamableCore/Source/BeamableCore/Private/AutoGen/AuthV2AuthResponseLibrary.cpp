
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2AuthResponseLibrary::AuthV2AuthResponseToJsonString(const UAuthV2AuthResponse* Serializable, const bool Pretty)
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

UAuthV2AuthResponse* UAuthV2AuthResponseLibrary::Make(FOptionalString AccessToken, FOptionalString RefreshToken, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2AuthResponse>(Outer);
	Serializable->AccessToken = AccessToken;
	Serializable->RefreshToken = RefreshToken;
	
	return Serializable;
}

void UAuthV2AuthResponseLibrary::Break(const UAuthV2AuthResponse* Serializable, FOptionalString& AccessToken, FOptionalString& RefreshToken)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AccessToken = Serializable->AccessToken;
		RefreshToken = Serializable->RefreshToken;
	}
		
}

