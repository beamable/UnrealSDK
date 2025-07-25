
#include "BeamableCore/Public/AutoGen/PlayerStatusUpdateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerStatusUpdateLibrary::PlayerStatusUpdateToJsonString(const UPlayerStatusUpdate* Serializable, const bool Pretty)
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

UPlayerStatusUpdate* UPlayerStatusUpdateLibrary::Make(FOptionalInt32 Tier, FOptionalInt32 Stage, FOptionalDouble Score, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerStatusUpdate>(Outer);
	Serializable->Tier = Tier;
	Serializable->Stage = Stage;
	Serializable->Score = Score;
	
	return Serializable;
}

void UPlayerStatusUpdateLibrary::Break(const UPlayerStatusUpdate* Serializable, FOptionalInt32& Tier, FOptionalInt32& Stage, FOptionalDouble& Score)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Tier = Serializable->Tier;
		Stage = Serializable->Stage;
		Score = Serializable->Score;
	}
		
}

