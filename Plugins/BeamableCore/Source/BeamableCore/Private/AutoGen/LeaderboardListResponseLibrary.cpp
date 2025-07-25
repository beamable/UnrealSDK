
#include "BeamableCore/Public/AutoGen/LeaderboardListResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardListResponseLibrary::LeaderboardListResponseToJsonString(const ULeaderboardListResponse* Serializable, const bool Pretty)
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

ULeaderboardListResponse* ULeaderboardListResponseLibrary::Make(int32 Total, int32 Offset, TArray<FString> NameList, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardListResponse>(Outer);
	Serializable->Total = Total;
	Serializable->Offset = Offset;
	Serializable->NameList = NameList;
	
	return Serializable;
}

void ULeaderboardListResponseLibrary::Break(const ULeaderboardListResponse* Serializable, int32& Total, int32& Offset, TArray<FString>& NameList)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Total = Serializable->Total;
		Offset = Serializable->Offset;
		NameList = Serializable->NameList;
	}
		
}

