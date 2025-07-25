
#include "BeamableCore/Public/AutoGen/LeaderboardPlayerAssignmentRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardPlayerAssignmentRequestBodyLibrary::LeaderboardPlayerAssignmentRequestBodyToJsonString(const ULeaderboardPlayerAssignmentRequestBody* Serializable, const bool Pretty)
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

ULeaderboardPlayerAssignmentRequestBody* ULeaderboardPlayerAssignmentRequestBodyLibrary::Make(FString BoardId, FOptionalBool bJoinBoard, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardPlayerAssignmentRequestBody>(Outer);
	Serializable->BoardId = BoardId;
	Serializable->bJoinBoard = bJoinBoard;
	
	return Serializable;
}

void ULeaderboardPlayerAssignmentRequestBodyLibrary::Break(const ULeaderboardPlayerAssignmentRequestBody* Serializable, FString& BoardId, FOptionalBool& bJoinBoard)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		BoardId = Serializable->BoardId;
		bJoinBoard = Serializable->bJoinBoard;
	}
		
}

