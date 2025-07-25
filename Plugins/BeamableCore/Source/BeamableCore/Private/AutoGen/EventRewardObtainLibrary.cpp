
#include "BeamableCore/Public/AutoGen/EventRewardObtainLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventRewardObtainLibrary::EventRewardObtainToJsonString(const UEventRewardObtain* Serializable, const bool Pretty)
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

UEventRewardObtain* UEventRewardObtainLibrary::Make(FString Symbol, int32 Count, UObject* Outer)
{
	auto Serializable = NewObject<UEventRewardObtain>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Count = Count;
	
	return Serializable;
}

void UEventRewardObtainLibrary::Break(const UEventRewardObtain* Serializable, FString& Symbol, int32& Count)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Count = Serializable->Count;
	}
		
}

