#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/SessionLanguageContext.h"

#include "OptionalSessionLanguageContext.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalSessionLanguageContextLibrary.MakeOptional", BeamOptionalType="USessionLanguageContext*"))
struct BEAMABLECORE_API FOptionalSessionLanguageContext : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USessionLanguageContext* Val;

	FOptionalSessionLanguageContext();

	explicit FOptionalSessionLanguageContext(USessionLanguageContext* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};