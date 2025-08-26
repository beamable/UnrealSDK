
#include "BeamableCore/Public/AutoGen/LeaderboardGetMatchRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardGetMatchRequestBodyLibrary::LeaderboardGetMatchRequestBodyToJsonString(const ULeaderboardGetMatchRequestBody* Serializable, const bool Pretty)
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

ULeaderboardGetMatchRequestBody* ULeaderboardGetMatchRequestBodyLibrary::Make(int32 PoolSize, int32 Windows, int32 WindowSize, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardGetMatchRequestBody>(Outer);
	Serializable->PoolSize = PoolSize;
	Serializable->Windows = Windows;
	Serializable->WindowSize = WindowSize;
	
	return Serializable;
}

void ULeaderboardGetMatchRequestBodyLibrary::Break(const ULeaderboardGetMatchRequestBody* Serializable, int32& PoolSize, int32& Windows, int32& WindowSize)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PoolSize = Serializable->PoolSize;
		Windows = Serializable->Windows;
		WindowSize = Serializable->WindowSize;
	}
		
}

