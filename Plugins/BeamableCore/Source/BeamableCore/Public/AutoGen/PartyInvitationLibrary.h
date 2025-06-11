#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PartyInvitation.h"

#include "PartyInvitationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPartyInvitationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Json", DisplayName="PartyInvitation To JSON String")
	static FString PartyInvitationToJsonString(const UPartyInvitation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Make PartyInvitation", meta=(DefaultToSelf="Outer", AdvancedDisplay="PartyId, InvitedBy, Outer", NativeMakeFunc))
	static UPartyInvitation* Make(FOptionalString PartyId, FOptionalString InvitedBy, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Break PartyInvitation", meta=(NativeBreakFunc))
	static void Break(const UPartyInvitation* Serializable, FOptionalString& PartyId, FOptionalString& InvitedBy);
};