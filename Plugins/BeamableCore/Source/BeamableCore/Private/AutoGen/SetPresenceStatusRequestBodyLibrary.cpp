
#include "BeamableCore/Public/AutoGen/SetPresenceStatusRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USetPresenceStatusRequestBodyLibrary::SetPresenceStatusRequestBodyToJsonString(const USetPresenceStatusRequestBody* Serializable, const bool Pretty)
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

USetPresenceStatusRequestBody* USetPresenceStatusRequestBodyLibrary::Make(FOptionalPresenceStatus Status, FOptionalString Description, UObject* Outer)
{
	auto Serializable = NewObject<USetPresenceStatusRequestBody>(Outer);
	Serializable->Status = Status;
	Serializable->Description = Description;
	
	return Serializable;
}

void USetPresenceStatusRequestBodyLibrary::Break(const USetPresenceStatusRequestBody* Serializable, FOptionalPresenceStatus& Status, FOptionalString& Description)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Status = Serializable->Status;
		Description = Serializable->Description;
	}
		
}

