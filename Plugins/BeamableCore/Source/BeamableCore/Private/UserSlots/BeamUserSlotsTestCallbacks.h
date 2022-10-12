#pragma once

#include "BeamUserSlots.spec.h"
#include "UserSlots/BeamUserSlots.h"

#include "BeamUserSlotsTestCallbacks.generated.h"

UCLASS()
class UBeamUserSlotsTestCallbacks final : public UObject
{
	GENERATED_BODY()

public:
	FBeamUserSlotsSpec* Spec;

	UPROPERTY()
	UBeamUserSlots* BeamUserSlots;

	// Forwarded data from the "Fake Request" we made.
	EUserSlotClearedReason ExpectedReason;
	FBeamRealmUser ExpectedRealmUser;
	
	// Done callback so that we can run latent tests correctly
	FDoneDelegate DoneDelegateForLatentTests;
};
