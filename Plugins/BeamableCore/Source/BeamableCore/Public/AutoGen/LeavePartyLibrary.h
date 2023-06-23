#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaveParty.h"

#include "LeavePartyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeavePartyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaveParty To JSON String")
	static FString LeavePartyToJsonString(const ULeaveParty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaveParty", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static ULeaveParty* Make(FOptionalString PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaveParty", meta=(NativeBreakFunc))
	static void Break(const ULeaveParty* Serializable, FOptionalString& PlayerId);
};