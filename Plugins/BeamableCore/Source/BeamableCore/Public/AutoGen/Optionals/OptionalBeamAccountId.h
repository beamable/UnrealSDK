#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamAccountId.h"

#include "OptionalBeamAccountId.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamAccountIdLibrary.MakeOptional", BeamOptionalType="FBeamAccountId"))
struct BEAMABLECORE_API FOptionalBeamAccountId : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamAccountId Val;

	FOptionalBeamAccountId();

	explicit FOptionalBeamAccountId(FBeamAccountId Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};