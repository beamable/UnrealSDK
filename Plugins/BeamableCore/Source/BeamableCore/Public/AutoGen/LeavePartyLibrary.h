#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaveParty.h"

#include "LeavePartyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeavePartyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Json", DisplayName="LeaveParty To JSON String")
	static FString LeavePartyToJsonString(const ULeaveParty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Make LeaveParty", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static ULeaveParty* Make(FOptionalBeamGamerTag PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Break LeaveParty", meta=(NativeBreakFunc))
	static void Break(const ULeaveParty* Serializable, FOptionalBeamGamerTag& PlayerId);
};