
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UnregisterDeviceTokenRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUnregisterDeviceTokenRequestArgsLibrary::UnregisterDeviceTokenRequestArgsToJsonString(const UUnregisterDeviceTokenRequestArgs* Serializable, const bool Pretty)
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

UUnregisterDeviceTokenRequestArgs* UUnregisterDeviceTokenRequestArgsLibrary::Make(FString Token, UObject* Outer)
{
	auto Serializable = NewObject<UUnregisterDeviceTokenRequestArgs>(Outer);
	Serializable->Token = Token;
	
	return Serializable;
}

void UUnregisterDeviceTokenRequestArgsLibrary::Break(const UUnregisterDeviceTokenRequestArgs* Serializable, FString& Token)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Token = Serializable->Token;
	}
		
}

