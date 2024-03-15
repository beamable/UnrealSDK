
#include "BeamableCore/Public/AutoGen/DeleteDevicesRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UDeleteDevicesRequestBodyLibrary::DeleteDevicesRequestBodyToJsonString(const UDeleteDevicesRequestBody* Serializable, const bool Pretty)
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

UDeleteDevicesRequestBody* UDeleteDevicesRequestBodyLibrary::Make(FOptionalArrayOfString DeviceIds, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteDevicesRequestBody>(Outer);
	Serializable->DeviceIds = DeviceIds;
	
	return Serializable;
}

void UDeleteDevicesRequestBodyLibrary::Break(const UDeleteDevicesRequestBody* Serializable, FOptionalArrayOfString& DeviceIds)
{
	DeviceIds = Serializable->DeviceIds;
		
}

