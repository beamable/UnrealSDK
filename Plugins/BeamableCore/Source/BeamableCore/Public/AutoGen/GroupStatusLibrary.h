#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupStatus.h"

#include "GroupStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="GroupStatus To JSON String")
	static FString GroupStatusToJsonString(const UGroupStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GroupStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="Completed, Outer", NativeMakeFunc))
	static UGroupStatus* Make(int32 LastUpdateCycle, FString TournamentId, int32 Stage, int32 Tier, int64 GroupId, FString ContentId, FOptionalArrayOfCompletedStatus Completed, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break GroupStatus", meta=(NativeBreakFunc))
	static void Break(const UGroupStatus* Serializable, int32& LastUpdateCycle, FString& TournamentId, int32& Stage, int32& Tier, int64& GroupId, FString& ContentId, FOptionalArrayOfCompletedStatus& Completed);
};