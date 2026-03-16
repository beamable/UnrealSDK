
#include "BeamableCore/Public/AutoGen/AuthV2ContextInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2ContextInfoLibrary::AuthV2ContextInfoToJsonString(const UAuthV2ContextInfo* Serializable, const bool Pretty)
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

UAuthV2ContextInfo* UAuthV2ContextInfoLibrary::Make(FOptionalString Platform, FOptionalString Device, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2ContextInfo>(Outer);
	Serializable->Platform = Platform;
	Serializable->Device = Device;
	
	return Serializable;
}

void UAuthV2ContextInfoLibrary::Break(const UAuthV2ContextInfo* Serializable, FOptionalString& Platform, FOptionalString& Device)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Platform = Serializable->Platform;
		Device = Serializable->Device;
	}
		
}

