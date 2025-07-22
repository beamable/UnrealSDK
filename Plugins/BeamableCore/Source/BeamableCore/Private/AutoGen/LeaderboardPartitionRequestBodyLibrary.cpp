
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardPartitionRequestBodyLibrary::LeaderboardPartitionRequestBodyToJsonString(const ULeaderboardPartitionRequestBody* Serializable, const bool Pretty)
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

ULeaderboardPartitionRequestBody* ULeaderboardPartitionRequestBodyLibrary::Make(int64 PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardPartitionRequestBody>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void ULeaderboardPartitionRequestBodyLibrary::Break(const ULeaderboardPartitionRequestBody* Serializable, int64& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

