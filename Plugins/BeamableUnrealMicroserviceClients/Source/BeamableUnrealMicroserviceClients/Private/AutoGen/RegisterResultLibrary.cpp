
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URegisterResultLibrary::RegisterResultToJsonString(const URegisterResult* Serializable, const bool Pretty)
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

URegisterResult* URegisterResultLibrary::Make(bool bSuccess, int32 DeviceCount, FString Message, UObject* Outer)
{
	auto Serializable = NewObject<URegisterResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->DeviceCount = DeviceCount;
	Serializable->Message = Message;
	
	return Serializable;
}

void URegisterResultLibrary::Break(const URegisterResult* Serializable, bool& bSuccess, int32& DeviceCount, FString& Message)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		DeviceCount = Serializable->DeviceCount;
		Message = Serializable->Message;
	}
		
}

