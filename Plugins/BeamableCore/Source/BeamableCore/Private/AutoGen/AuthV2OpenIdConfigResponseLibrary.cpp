
#include "BeamableCore/Public/AutoGen/AuthV2OpenIdConfigResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2OpenIdConfigResponseLibrary::AuthV2OpenIdConfigResponseToJsonString(const UAuthV2OpenIdConfigResponse* Serializable, const bool Pretty)
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

UAuthV2OpenIdConfigResponse* UAuthV2OpenIdConfigResponseLibrary::Make(FString Issuer, FString JwksUri, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2OpenIdConfigResponse>(Outer);
	Serializable->Issuer = Issuer;
	Serializable->JwksUri = JwksUri;
	
	return Serializable;
}

void UAuthV2OpenIdConfigResponseLibrary::Break(const UAuthV2OpenIdConfigResponse* Serializable, FString& Issuer, FString& JwksUri)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Issuer = Serializable->Issuer;
		JwksUri = Serializable->JwksUri;
	}
		
}

