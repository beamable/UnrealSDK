
#include "BeamableCore/Public/AutoGen/NetworkSerializableLibrary.h"

#include "CoreMinimal.h"


FString UNetworkSerializableLibrary::NetworkSerializableToJsonString(const UNetworkSerializable* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
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



