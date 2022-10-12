
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/ContextInfo.h"

#include "OptionalContextInfo.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalContextInfoLibrary.MakeOptionalContextInfo"))
struct FOptionalContextInfo : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UContextInfo* Val;

	FOptionalContextInfo();

	explicit FOptionalContextInfo(UContextInfo* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};