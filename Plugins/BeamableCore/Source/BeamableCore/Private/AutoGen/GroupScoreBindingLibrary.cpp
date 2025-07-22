
#include "BeamableCore/Public/AutoGen/GroupScoreBindingLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupScoreBindingLibrary::GroupScoreBindingToJsonString(const UGroupScoreBinding* Serializable, const bool Pretty)
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

UGroupScoreBinding* UGroupScoreBindingLibrary::Make(FString Board, int64 Score, TArray<FString> Derivatives, UObject* Outer)
{
	auto Serializable = NewObject<UGroupScoreBinding>(Outer);
	Serializable->Board = Board;
	Serializable->Score = Score;
	Serializable->Derivatives = Derivatives;
	
	return Serializable;
}

void UGroupScoreBindingLibrary::Break(const UGroupScoreBinding* Serializable, FString& Board, int64& Score, TArray<FString>& Derivatives)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Board = Serializable->Board;
		Score = Serializable->Score;
		Derivatives = Serializable->Derivatives;
	}
		
}

