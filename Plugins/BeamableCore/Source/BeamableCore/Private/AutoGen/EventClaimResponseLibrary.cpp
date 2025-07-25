
#include "BeamableCore/Public/AutoGen/EventClaimResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventClaimResponseLibrary::EventClaimResponseToJsonString(const UEventClaimResponse* Serializable, const bool Pretty)
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

UEventClaimResponse* UEventClaimResponseLibrary::Make(UEventPlayerStateView* View, FString GameRspJson, UObject* Outer)
{
	auto Serializable = NewObject<UEventClaimResponse>(Outer);
	Serializable->View = View;
	Serializable->GameRspJson = GameRspJson;
	
	return Serializable;
}

void UEventClaimResponseLibrary::Break(const UEventClaimResponse* Serializable, UEventPlayerStateView*& View, FString& GameRspJson)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		View = Serializable->View;
		GameRspJson = Serializable->GameRspJson;
	}
		
}

