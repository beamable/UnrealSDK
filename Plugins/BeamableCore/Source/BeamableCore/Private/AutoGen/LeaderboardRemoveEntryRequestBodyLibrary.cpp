
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveEntryRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardRemoveEntryRequestBodyLibrary::LeaderboardRemoveEntryRequestBodyToJsonString(const ULeaderboardRemoveEntryRequestBody* Serializable, const bool Pretty)
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

ULeaderboardRemoveEntryRequestBody* ULeaderboardRemoveEntryRequestBodyLibrary::Make(int64 Id, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardRemoveEntryRequestBody>(Outer);
	Serializable->Id = Id;
	
	return Serializable;
}

void ULeaderboardRemoveEntryRequestBodyLibrary::Break(const ULeaderboardRemoveEntryRequestBody* Serializable, int64& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
	}
		
}

