
#include "BeamableCore/Public/AutoGen/LeaderboardSwapRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardSwapRequestBodyLibrary::LeaderboardSwapRequestBodyToJsonString(const ULeaderboardSwapRequestBody* Serializable, const bool Pretty)
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

ULeaderboardSwapRequestBody* ULeaderboardSwapRequestBodyLibrary::Make(int64 SwapBase, int64 Delta, FOptionalInt64 WinnerId, FOptionalInt64 LoserId, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardSwapRequestBody>(Outer);
	Serializable->SwapBase = SwapBase;
	Serializable->Delta = Delta;
	Serializable->WinnerId = WinnerId;
	Serializable->LoserId = LoserId;
	
	return Serializable;
}

void ULeaderboardSwapRequestBodyLibrary::Break(const ULeaderboardSwapRequestBody* Serializable, int64& SwapBase, int64& Delta, FOptionalInt64& WinnerId, FOptionalInt64& LoserId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SwapBase = Serializable->SwapBase;
		Delta = Serializable->Delta;
		WinnerId = Serializable->WinnerId;
		LoserId = Serializable->LoserId;
	}
		
}

