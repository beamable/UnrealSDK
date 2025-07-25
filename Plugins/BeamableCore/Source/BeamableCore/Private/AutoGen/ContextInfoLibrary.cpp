
#include "BeamableCore/Public/AutoGen/ContextInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UContextInfoLibrary::ContextInfoToJsonString(const UContextInfo* Serializable, const bool Pretty)
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

UContextInfo* UContextInfoLibrary::Make(FOptionalString Platform, FOptionalString Device, UObject* Outer)
{
	auto Serializable = NewObject<UContextInfo>(Outer);
	Serializable->Platform = Platform;
	Serializable->Device = Device;
	
	return Serializable;
}

void UContextInfoLibrary::Break(const UContextInfo* Serializable, FOptionalString& Platform, FOptionalString& Device)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Platform = Serializable->Platform;
		Device = Serializable->Device;
	}
		
}

