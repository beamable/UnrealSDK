
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterDeviceTokenRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URegisterDeviceTokenRequestArgsLibrary::RegisterDeviceTokenRequestArgsToJsonString(const URegisterDeviceTokenRequestArgs* Serializable, const bool Pretty)
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

URegisterDeviceTokenRequestArgs* URegisterDeviceTokenRequestArgsLibrary::Make(FString Token, FString Environment, FString Platform, UObject* Outer)
{
	auto Serializable = NewObject<URegisterDeviceTokenRequestArgs>(Outer);
	Serializable->Token = Token;
	Serializable->Environment = Environment;
	Serializable->Platform = Platform;
	
	return Serializable;
}

void URegisterDeviceTokenRequestArgsLibrary::Break(const URegisterDeviceTokenRequestArgs* Serializable, FString& Token, FString& Environment, FString& Platform)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Token = Serializable->Token;
		Environment = Serializable->Environment;
		Platform = Serializable->Platform;
	}
		
}

