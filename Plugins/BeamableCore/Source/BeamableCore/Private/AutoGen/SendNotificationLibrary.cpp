
#include "BeamableCore/Public/AutoGen/SendNotificationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendNotificationLibrary::SendNotificationToJsonString(const USendNotification* Serializable, const bool Pretty)
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

USendNotification* USendNotificationLibrary::Make(FOptionalString Title, FOptionalString Body, UObject* Outer)
{
	auto Serializable = NewObject<USendNotification>(Outer);
	Serializable->Title = Title;
	Serializable->Body = Body;
	
	return Serializable;
}

void USendNotificationLibrary::Break(const USendNotification* Serializable, FOptionalString& Title, FOptionalString& Body)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Title = Serializable->Title;
		Body = Serializable->Body;
	}
		
}

