
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeviceInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeviceInfoLibrary::DeviceInfoToJsonString(const UDeviceInfo* Serializable, const bool Pretty)
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

UDeviceInfo* UDeviceInfoLibrary::Make(FString Token, FString Platform, FString Environment, int64 UpdatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UDeviceInfo>(Outer);
	Serializable->Token = Token;
	Serializable->Platform = Platform;
	Serializable->Environment = Environment;
	Serializable->UpdatedAt = UpdatedAt;
	
	return Serializable;
}

void UDeviceInfoLibrary::Break(const UDeviceInfo* Serializable, FString& Token, FString& Platform, FString& Environment, int64& UpdatedAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Token = Serializable->Token;
		Platform = Serializable->Platform;
		Environment = Serializable->Environment;
		UpdatedAt = Serializable->UpdatedAt;
	}
		
}

