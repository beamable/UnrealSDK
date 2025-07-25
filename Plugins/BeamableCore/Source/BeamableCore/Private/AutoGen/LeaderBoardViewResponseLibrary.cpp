
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderBoardViewResponseLibrary::LeaderBoardViewResponseToJsonString(const ULeaderBoardViewResponse* Serializable, const bool Pretty)
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

ULeaderBoardViewResponse* ULeaderBoardViewResponseLibrary::Make(FString Result, ULeaderBoardView* Lb, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderBoardViewResponse>(Outer);
	Serializable->Result = Result;
	Serializable->Lb = Lb;
	
	return Serializable;
}

void ULeaderBoardViewResponseLibrary::Break(const ULeaderBoardViewResponse* Serializable, FString& Result, ULeaderBoardView*& Lb)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
		Lb = Serializable->Lb;
	}
		
}

