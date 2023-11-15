#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Tag.h"

#include "OptionalArrayOfTag.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfTagLibrary.MakeOptional", BeamOptionalType="TArray<UTag*>"))
struct BEAMABLECORE_API FOptionalArrayOfTag : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UTag*> Val;

	FOptionalArrayOfTag();

	explicit FOptionalArrayOfTag(TArray<UTag*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};