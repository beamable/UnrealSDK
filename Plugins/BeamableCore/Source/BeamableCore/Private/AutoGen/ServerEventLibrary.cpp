
#include "BeamableCore/Public/AutoGen/ServerEventLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServerEventLibrary::ServerEventToJsonString(const UServerEvent* Serializable, const bool Pretty)
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

UServerEvent* UServerEventLibrary::Make(FString Event, bool bToAll, FOptionalString Payload, UObject* Outer)
{
	auto Serializable = NewObject<UServerEvent>(Outer);
	Serializable->Event = Event;
	Serializable->bToAll = bToAll;
	Serializable->Payload = Payload;
	
	return Serializable;
}

void UServerEventLibrary::Break(const UServerEvent* Serializable, FString& Event, bool& bToAll, FOptionalString& Payload)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Event = Serializable->Event;
		bToAll = Serializable->bToAll;
		Payload = Serializable->Payload;
	}
		
}

