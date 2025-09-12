#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ContentTagFilter.h"

#include "OptionalContentTagFilter.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalContentTagFilterLibrary.MakeOptional", BeamOptionalType="UContentTagFilter*"))
struct BEAMABLECORE_API FOptionalContentTagFilter : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UContentTagFilter* Val;

	FOptionalContentTagFilter();

	explicit FOptionalContentTagFilter(UContentTagFilter* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};