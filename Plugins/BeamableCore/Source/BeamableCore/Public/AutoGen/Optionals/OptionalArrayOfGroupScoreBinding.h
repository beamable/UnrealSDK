
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/GroupScoreBinding.h"

#include "OptionalArrayOfGroupScoreBinding.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfGroupScoreBindingLibrary.MakeOptionalArrayOfGroupScoreBinding"))
struct FOptionalArrayOfGroupScoreBinding : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UGroupScoreBinding*> Val;

	FOptionalArrayOfGroupScoreBinding();

	explicit FOptionalArrayOfGroupScoreBinding(TArray<UGroupScoreBinding*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};