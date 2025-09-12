#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/PropertyFilterDTO.h"

#include "OptionalArrayOfPropertyFilterDTO.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfPropertyFilterDTOLibrary.MakeOptional", BeamOptionalType="TArray<UPropertyFilterDTO*>"))
struct BEAMABLECORE_API FOptionalArrayOfPropertyFilterDTO : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UPropertyFilterDTO*> Val;

	FOptionalArrayOfPropertyFilterDTO();

	explicit FOptionalArrayOfPropertyFilterDTO(TArray<UPropertyFilterDTO*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};