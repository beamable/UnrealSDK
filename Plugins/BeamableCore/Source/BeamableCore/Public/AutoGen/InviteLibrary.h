#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Invite.h"

#include "InviteLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInviteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|4 - Json", DisplayName="Invite To JSON String")
	static FString InviteToJsonString(const UInvite* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|3 - Backend", DisplayName="Make Invite", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UInvite* Make(FBeamGamerTag PlayerId, EInvitationDirection Direction, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|3 - Backend", DisplayName="Break Invite", meta=(NativeBreakFunc))
	static void Break(const UInvite* Serializable, FBeamGamerTag& PlayerId, EInvitationDirection& Direction);
};