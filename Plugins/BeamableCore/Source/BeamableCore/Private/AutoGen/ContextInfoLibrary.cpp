
#include "BeamableCore/Public/AutoGen/ContextInfoLibrary.h"

#include "CoreMinimal.h"


FString UContextInfoLibrary::ContextInfoToJsonString(const UContextInfo* Serializable, const bool Pretty)
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

UContextInfo* UContextInfoLibrary::Make(FString Platform, FString Device, UObject* Outer)
{
	auto Serializable = NewObject<UContextInfo>(Outer);
	Serializable->Platform = Platform;
	Serializable->Device = Device;
	
	return Serializable;
}

void UContextInfoLibrary::Break(const UContextInfo* Serializable, FString& Platform, FString& Device)
{
	Platform = Serializable->Platform;
	Device = Serializable->Device;
		
}

