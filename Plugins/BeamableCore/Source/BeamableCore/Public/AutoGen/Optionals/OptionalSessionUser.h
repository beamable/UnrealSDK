#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/SessionUser.h"

#include "OptionalSessionUser.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalSessionUserLibrary.MakeOptional", BeamOptionalType="USessionUser*"))
struct BEAMABLECORE_API FOptionalSessionUser : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	USessionUser* Val;

	FOptionalSessionUser();

	explicit FOptionalSessionUser(USessionUser* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};