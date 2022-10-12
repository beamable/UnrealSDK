
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/EntitlementClaimWindow.h"

#include "OptionalEntitlementClaimWindow.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalEntitlementClaimWindowLibrary.MakeOptionalEntitlementClaimWindow"))
struct FOptionalEntitlementClaimWindow : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UEntitlementClaimWindow* Val;

	FOptionalEntitlementClaimWindow();

	explicit FOptionalEntitlementClaimWindow(UEntitlementClaimWindow* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};