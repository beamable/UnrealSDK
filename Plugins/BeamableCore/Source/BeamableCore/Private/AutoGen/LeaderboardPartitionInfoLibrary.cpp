
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardPartitionInfoLibrary::LeaderboardPartitionInfoToJsonString(const ULeaderboardPartitionInfo* Serializable, const bool Pretty)
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

ULeaderboardPartitionInfo* ULeaderboardPartitionInfoLibrary::Make(bool bIsEmpty, int64 PlayerId, FString LeaderboardId, FOptionalInt32 Partition, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardPartitionInfo>(Outer);
	Serializable->bIsEmpty = bIsEmpty;
	Serializable->PlayerId = PlayerId;
	Serializable->LeaderboardId = LeaderboardId;
	Serializable->Partition = Partition;
	
	return Serializable;
}

void ULeaderboardPartitionInfoLibrary::Break(const ULeaderboardPartitionInfo* Serializable, bool& bIsEmpty, int64& PlayerId, FString& LeaderboardId, FOptionalInt32& Partition)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsEmpty = Serializable->bIsEmpty;
		PlayerId = Serializable->PlayerId;
		LeaderboardId = Serializable->LeaderboardId;
		Partition = Serializable->Partition;
	}
		
}

