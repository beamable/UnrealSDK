#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Invite.h"

#include "InviteLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInviteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="Invite To JSON String")
	static FString InviteToJsonString(const UInvite* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make Invite", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UInvite* Make(FBeamGamerTag PlayerId, EBeamInvitationDirection Direction, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break Invite", meta=(NativeBreakFunc))
	static void Break(const UInvite* Serializable, FBeamGamerTag& PlayerId, EBeamInvitationDirection& Direction);
};