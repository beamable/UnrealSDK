
#include "BeamableCore/Public/AutoGen/LeaderBoardViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderBoardViewLibrary::LeaderBoardViewToJsonString(const ULeaderBoardView* Serializable, const bool Pretty)
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

ULeaderBoardView* ULeaderBoardViewLibrary::Make(FString LbId, int64 BoardSize, TArray<URankEntry*> Rankings, FOptionalRankEntry Rankgt, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderBoardView>(Outer);
	Serializable->LbId = LbId;
	Serializable->BoardSize = BoardSize;
	Serializable->Rankings = Rankings;
	Serializable->Rankgt = Rankgt;
	
	return Serializable;
}

void ULeaderBoardViewLibrary::Break(const ULeaderBoardView* Serializable, FString& LbId, int64& BoardSize, TArray<URankEntry*>& Rankings, FOptionalRankEntry& Rankgt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		LbId = Serializable->LbId;
		BoardSize = Serializable->BoardSize;
		Rankings = Serializable->Rankings;
		Rankgt = Serializable->Rankgt;
	}
		
}

