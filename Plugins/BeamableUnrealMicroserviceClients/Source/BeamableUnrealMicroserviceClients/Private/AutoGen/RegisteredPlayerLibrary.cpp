
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisteredPlayerLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URegisteredPlayerLibrary::RegisteredPlayerToJsonString(const URegisteredPlayer* Serializable, const bool Pretty)
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

URegisteredPlayer* URegisteredPlayerLibrary::Make(int64 PlayerId, int32 DeviceCount, int64 LastUpdated, FString GamePlatform, FString GameDevice, TArray<FString> Platforms, UObject* Outer)
{
	auto Serializable = NewObject<URegisteredPlayer>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->DeviceCount = DeviceCount;
	Serializable->LastUpdated = LastUpdated;
	Serializable->GamePlatform = GamePlatform;
	Serializable->GameDevice = GameDevice;
	Serializable->Platforms = Platforms;
	
	return Serializable;
}

void URegisteredPlayerLibrary::Break(const URegisteredPlayer* Serializable, int64& PlayerId, int32& DeviceCount, int64& LastUpdated, FString& GamePlatform, FString& GameDevice, TArray<FString>& Platforms)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		DeviceCount = Serializable->DeviceCount;
		LastUpdated = Serializable->LastUpdated;
		GamePlatform = Serializable->GamePlatform;
		GameDevice = Serializable->GameDevice;
		Platforms = Serializable->Platforms;
	}
		
}

