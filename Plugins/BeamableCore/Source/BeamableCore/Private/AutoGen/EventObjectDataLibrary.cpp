
#include "BeamableCore/Public/AutoGen/EventObjectDataLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventObjectDataLibrary::EventObjectDataToJsonString(const UEventObjectData* Serializable, const bool Pretty)
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

UEventObjectData* UEventObjectDataLibrary::Make(bool bDone, bool bRunning, EBeamEventState State, FString LeaderboardId, FString Id, UEvent* Content, FOptionalString LastChildEventId, FOptionalInt64 StartTime, FOptionalString RootEventId, FOptionalString OriginType, FOptionalEventPhaseRuntime Phase, FOptionalBeamClientPermission Permissions, FOptionalInt64 EndTime, FOptionalString Origin, FOptionalInt64 CreatedAt, FOptionalArrayOfInFlightMessage InFlight, FOptionalArrayOfEventPhaseTime PhaseTimes, UObject* Outer)
{
	auto Serializable = NewObject<UEventObjectData>(Outer);
	Serializable->bDone = bDone;
	Serializable->bRunning = bRunning;
	Serializable->State = State;
	Serializable->LeaderboardId = LeaderboardId;
	Serializable->Id = Id;
	Serializable->Content = Content;
	Serializable->LastChildEventId = LastChildEventId;
	Serializable->StartTime = StartTime;
	Serializable->RootEventId = RootEventId;
	Serializable->OriginType = OriginType;
	Serializable->Phase = Phase;
	Serializable->Permissions = Permissions;
	Serializable->EndTime = EndTime;
	Serializable->Origin = Origin;
	Serializable->CreatedAt = CreatedAt;
	Serializable->InFlight = InFlight;
	Serializable->PhaseTimes = PhaseTimes;
	
	return Serializable;
}

void UEventObjectDataLibrary::Break(const UEventObjectData* Serializable, bool& bDone, bool& bRunning, EBeamEventState& State, FString& LeaderboardId, FString& Id, UEvent*& Content, FOptionalString& LastChildEventId, FOptionalInt64& StartTime, FOptionalString& RootEventId, FOptionalString& OriginType, FOptionalEventPhaseRuntime& Phase, FOptionalBeamClientPermission& Permissions, FOptionalInt64& EndTime, FOptionalString& Origin, FOptionalInt64& CreatedAt, FOptionalArrayOfInFlightMessage& InFlight, FOptionalArrayOfEventPhaseTime& PhaseTimes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bDone = Serializable->bDone;
		bRunning = Serializable->bRunning;
		State = Serializable->State;
		LeaderboardId = Serializable->LeaderboardId;
		Id = Serializable->Id;
		Content = Serializable->Content;
		LastChildEventId = Serializable->LastChildEventId;
		StartTime = Serializable->StartTime;
		RootEventId = Serializable->RootEventId;
		OriginType = Serializable->OriginType;
		Phase = Serializable->Phase;
		Permissions = Serializable->Permissions;
		EndTime = Serializable->EndTime;
		Origin = Serializable->Origin;
		CreatedAt = Serializable->CreatedAt;
		InFlight = Serializable->InFlight;
		PhaseTimes = Serializable->PhaseTimes;
	}
		
}

