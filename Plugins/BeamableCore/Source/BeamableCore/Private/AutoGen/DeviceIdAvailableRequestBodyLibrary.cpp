
#include "BeamableCore/Public/AutoGen/DeviceIdAvailableRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeviceIdAvailableRequestBodyLibrary::DeviceIdAvailableRequestBodyToJsonString(const UDeviceIdAvailableRequestBody* Serializable, const bool Pretty)
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

UDeviceIdAvailableRequestBody* UDeviceIdAvailableRequestBodyLibrary::Make(FString DeviceId, UObject* Outer)
{
	auto Serializable = NewObject<UDeviceIdAvailableRequestBody>(Outer);
	Serializable->DeviceId = DeviceId;
	
	return Serializable;
}

void UDeviceIdAvailableRequestBodyLibrary::Break(const UDeviceIdAvailableRequestBody* Serializable, FString& DeviceId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		DeviceId = Serializable->DeviceId;
	}
		
}

