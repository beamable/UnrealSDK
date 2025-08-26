
#include "BeamableCore/Public/AutoGen/EventPlayerViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventPlayerViewLibrary::EventPlayerViewToJsonString(const UEventPlayerView* Serializable, const bool Pretty)
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

UEventPlayerView* UEventPlayerViewLibrary::Make(TArray<UEventPlayerStateView*> Running, TArray<UEventPlayerStateView*> Done, UObject* Outer)
{
	auto Serializable = NewObject<UEventPlayerView>(Outer);
	Serializable->Running = Running;
	Serializable->Done = Done;
	
	return Serializable;
}

void UEventPlayerViewLibrary::Break(const UEventPlayerView* Serializable, TArray<UEventPlayerStateView*>& Running, TArray<UEventPlayerStateView*>& Done)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Running = Serializable->Running;
		Done = Serializable->Done;
	}
		
}

