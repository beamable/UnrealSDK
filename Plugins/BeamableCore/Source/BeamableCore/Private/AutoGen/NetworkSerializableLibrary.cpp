
#include "BeamableCore/Public/AutoGen/NetworkSerializableLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UNetworkSerializableLibrary::NetworkSerializableToJsonString(const UNetworkSerializable* Serializable, const bool Pretty)
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

UNetworkSerializable* UNetworkSerializableLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UNetworkSerializable>(Outer);
	
	return Serializable;
}



