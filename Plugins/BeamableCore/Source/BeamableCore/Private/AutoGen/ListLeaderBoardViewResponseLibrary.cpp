
#include "BeamableCore/Public/AutoGen/ListLeaderBoardViewResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListLeaderBoardViewResponseLibrary::ListLeaderBoardViewResponseToJsonString(const UListLeaderBoardViewResponse* Serializable, const bool Pretty)
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

UListLeaderBoardViewResponse* UListLeaderBoardViewResponseLibrary::Make(FString Result, TArray<ULeaderBoardView*> Lbs, UObject* Outer)
{
	auto Serializable = NewObject<UListLeaderBoardViewResponse>(Outer);
	Serializable->Result = Result;
	Serializable->Lbs = Lbs;
	
	return Serializable;
}

void UListLeaderBoardViewResponseLibrary::Break(const UListLeaderBoardViewResponse* Serializable, FString& Result, TArray<ULeaderBoardView*>& Lbs)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
		Lbs = Serializable->Lbs;
	}
		
}

