#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventObjectData.h"

#include "EventObjectDataLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventObjectDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventObjectData To JSON String")
	static FString EventObjectDataToJsonString(const UEventObjectData* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventObjectData", meta=(DefaultToSelf="Outer", AdvancedDisplay="LastChildEventId, StartTime, RootEventId, OriginType, Phase, Permissions, EndTime, Origin, CreatedAt, InFlight, PhaseTimes, Outer", NativeMakeFunc))
	static UEventObjectData* Make(bool bDone, bool bRunning, EBeamEventState State, FString LeaderboardId, FString Id, UEvent* Content, FOptionalString LastChildEventId, FOptionalInt64 StartTime, FOptionalString RootEventId, FOptionalString OriginType, FOptionalEventPhaseRuntime Phase, FOptionalBeamClientPermission Permissions, FOptionalInt64 EndTime, FOptionalString Origin, FOptionalInt64 CreatedAt, FOptionalArrayOfInFlightMessage InFlight, FOptionalArrayOfEventPhaseTime PhaseTimes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventObjectData", meta=(NativeBreakFunc))
	static void Break(const UEventObjectData* Serializable, bool& bDone, bool& bRunning, EBeamEventState& State, FString& LeaderboardId, FString& Id, UEvent*& Content, FOptionalString& LastChildEventId, FOptionalInt64& StartTime, FOptionalString& RootEventId, FOptionalString& OriginType, FOptionalEventPhaseRuntime& Phase, FOptionalBeamClientPermission& Permissions, FOptionalInt64& EndTime, FOptionalString& Origin, FOptionalInt64& CreatedAt, FOptionalArrayOfInFlightMessage& InFlight, FOptionalArrayOfEventPhaseTime& PhaseTimes);
};