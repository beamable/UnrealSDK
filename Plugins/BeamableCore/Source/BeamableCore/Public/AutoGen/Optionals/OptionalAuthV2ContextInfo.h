#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AuthV2ContextInfo.h"

#include "OptionalAuthV2ContextInfo.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalAuthV2ContextInfoLibrary.MakeOptional", BeamOptionalType="UAuthV2ContextInfo*"))
struct BEAMABLECORE_API FOptionalAuthV2ContextInfo : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAuthV2ContextInfo* Val;

	FOptionalAuthV2ContextInfo();

	explicit FOptionalAuthV2ContextInfo(UAuthV2ContextInfo* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};