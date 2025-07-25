
#include "BeamableCore/Public/AutoGen/WebSocketConfigurationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UWebSocketConfigurationLibrary::WebSocketConfigurationToJsonString(const UWebSocketConfiguration* Serializable, const bool Pretty)
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

UWebSocketConfiguration* UWebSocketConfigurationLibrary::Make(FString Provider, FOptionalString Uri, UObject* Outer)
{
	auto Serializable = NewObject<UWebSocketConfiguration>(Outer);
	Serializable->Provider = Provider;
	Serializable->Uri = Uri;
	
	return Serializable;
}

void UWebSocketConfigurationLibrary::Break(const UWebSocketConfiguration* Serializable, FString& Provider, FOptionalString& Uri)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Provider = Serializable->Provider;
		Uri = Serializable->Uri;
	}
		
}

