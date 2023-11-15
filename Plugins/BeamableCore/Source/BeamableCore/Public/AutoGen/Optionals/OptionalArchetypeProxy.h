#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ArchetypeProxy.h"

#include "OptionalArchetypeProxy.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArchetypeProxyLibrary.MakeOptional", BeamOptionalType="UArchetypeProxy*"))
struct BEAMABLECORE_API FOptionalArchetypeProxy : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UArchetypeProxy* Val;

	FOptionalArchetypeProxy();

	explicit FOptionalArchetypeProxy(UArchetypeProxy* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};