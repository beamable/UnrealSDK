
#include "BeamableCore/Public/AutoGen/GroupStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupStatusLibrary::GroupStatusToJsonString(const UGroupStatus* Serializable, const bool Pretty)
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

UGroupStatus* UGroupStatusLibrary::Make(int32 LastUpdateCycle, FString TournamentId, int32 Stage, int32 Tier, int64 GroupId, FString ContentId, FOptionalArrayOfCompletedStatus Completed, UObject* Outer)
{
	auto Serializable = NewObject<UGroupStatus>(Outer);
	Serializable->LastUpdateCycle = LastUpdateCycle;
	Serializable->TournamentId = TournamentId;
	Serializable->Stage = Stage;
	Serializable->Tier = Tier;
	Serializable->GroupId = GroupId;
	Serializable->ContentId = ContentId;
	Serializable->Completed = Completed;
	
	return Serializable;
}

void UGroupStatusLibrary::Break(const UGroupStatus* Serializable, int32& LastUpdateCycle, FString& TournamentId, int32& Stage, int32& Tier, int64& GroupId, FString& ContentId, FOptionalArrayOfCompletedStatus& Completed)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		LastUpdateCycle = Serializable->LastUpdateCycle;
		TournamentId = Serializable->TournamentId;
		Stage = Serializable->Stage;
		Tier = Serializable->Tier;
		GroupId = Serializable->GroupId;
		ContentId = Serializable->ContentId;
		Completed = Serializable->Completed;
	}
		
}

