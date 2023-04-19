
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ExternalIdentity.h"

#include "OptionalArrayOfExternalIdentity.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfExternalIdentityLibrary.MakeOptional", BeamOptionalType="TArray<UExternalIdentity*>"))
struct BEAMABLECORE_API FOptionalArrayOfExternalIdentity : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UExternalIdentity*> Val;

	FOptionalArrayOfExternalIdentity();

	explicit FOptionalArrayOfExternalIdentity(TArray<UExternalIdentity*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};