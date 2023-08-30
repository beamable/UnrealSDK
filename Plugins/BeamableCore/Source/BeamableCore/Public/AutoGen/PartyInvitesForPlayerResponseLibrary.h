#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PartyInvitesForPlayerResponse.h"

#include "PartyInvitesForPlayerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPartyInvitesForPlayerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PartyInvitesForPlayerResponse To JSON String")
	static FString PartyInvitesForPlayerResponseToJsonString(const UPartyInvitesForPlayerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PartyInvitesForPlayerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Invitations, Outer", NativeMakeFunc))
	static UPartyInvitesForPlayerResponse* Make(FOptionalArrayOfPartyInvitation Invitations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PartyInvitesForPlayerResponse", meta=(NativeBreakFunc))
	static void Break(const UPartyInvitesForPlayerResponse* Serializable, FOptionalArrayOfPartyInvitation& Invitations);
};