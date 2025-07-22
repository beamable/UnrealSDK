
#include "BeamableCore/Public/AutoGen/LeaderboardDetailsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardDetailsRequestBodyLibrary::LeaderboardDetailsRequestBodyToJsonString(const ULeaderboardDetailsRequestBody* Serializable, const bool Pretty)
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

ULeaderboardDetailsRequestBody* ULeaderboardDetailsRequestBodyLibrary::Make(FOptionalInt32 From, FOptionalInt32 Max, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardDetailsRequestBody>(Outer);
	Serializable->From = From;
	Serializable->Max = Max;
	
	return Serializable;
}

void ULeaderboardDetailsRequestBodyLibrary::Break(const ULeaderboardDetailsRequestBody* Serializable, FOptionalInt32& From, FOptionalInt32& Max)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		From = Serializable->From;
		Max = Serializable->Max;
	}
		
}

