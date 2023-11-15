#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ContextInfo.h"

#include "OptionalContextInfo.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalContextInfoLibrary.MakeOptional", BeamOptionalType="UContextInfo*"))
struct BEAMABLECORE_API FOptionalContextInfo : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UContextInfo* Val;

	FOptionalContextInfo();

	explicit FOptionalContextInfo(UContextInfo* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};