#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/CohortEntry.h"

#include "OptionalArrayOfCohortEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfCohortEntryLibrary.MakeOptional", BeamOptionalType="TArray<UCohortEntry*>"))
struct BEAMABLECORE_API FOptionalArrayOfCohortEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UCohortEntry*> Val;

	FOptionalArrayOfCohortEntry();

	explicit FOptionalArrayOfCohortEntry(TArray<UCohortEntry*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};