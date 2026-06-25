
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeviceListLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeviceListLibrary::DeviceListToJsonString(const UDeviceList* Serializable, const bool Pretty)
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

UDeviceList* UDeviceListLibrary::Make(TArray<UDeviceInfo*> Devices, UObject* Outer)
{
	auto Serializable = NewObject<UDeviceList>(Outer);
	Serializable->Devices = Devices;
	
	return Serializable;
}

void UDeviceListLibrary::Break(const UDeviceList* Serializable, TArray<UDeviceInfo*>& Devices)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Devices = Serializable->Devices;
	}
		
}

