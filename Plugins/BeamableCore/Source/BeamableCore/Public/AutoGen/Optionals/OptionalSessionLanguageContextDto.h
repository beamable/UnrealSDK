#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/SessionLanguageContextDto.h"

#include "OptionalSessionLanguageContextDto.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalSessionLanguageContextDtoLibrary.MakeOptional", BeamOptionalType="USessionLanguageContextDto*"))
struct BEAMABLECORE_API FOptionalSessionLanguageContextDto : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USessionLanguageContextDto* Val;

	FOptionalSessionLanguageContextDto();

	explicit FOptionalSessionLanguageContextDto(USessionLanguageContextDto* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};