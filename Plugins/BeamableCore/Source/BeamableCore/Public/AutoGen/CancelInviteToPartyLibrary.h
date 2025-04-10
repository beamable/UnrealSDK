#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CancelInviteToParty.h"

#include "CancelInviteToPartyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCancelInviteToPartyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|4 - Json", DisplayName="CancelInviteToParty To JSON String")
	static FString CancelInviteToPartyToJsonString(const UCancelInviteToParty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|3 - Backend", DisplayName="Make CancelInviteToParty", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static UCancelInviteToParty* Make(FOptionalBeamGamerTag PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Party|3 - Backend", DisplayName="Break CancelInviteToParty", meta=(NativeBreakFunc))
	static void Break(const UCancelInviteToParty* Serializable, FOptionalBeamGamerTag& PlayerId);
};