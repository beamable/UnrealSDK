
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/PlayerStatRequirement.h"

#include "OptionalArrayOfPlayerStatRequirement.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfPlayerStatRequirementLibrary.MakeOptionalArrayOfPlayerStatRequirement"))
struct FOptionalArrayOfPlayerStatRequirement : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UPlayerStatRequirement*> Val;

	FOptionalArrayOfPlayerStatRequirement();

	explicit FOptionalArrayOfPlayerStatRequirement(TArray<UPlayerStatRequirement*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};