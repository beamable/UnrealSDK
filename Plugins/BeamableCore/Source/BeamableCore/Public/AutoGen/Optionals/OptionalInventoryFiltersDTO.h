#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/InventoryFiltersDTO.h"

#include "OptionalInventoryFiltersDTO.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalInventoryFiltersDTOLibrary.MakeOptional", BeamOptionalType="UInventoryFiltersDTO*"))
struct BEAMABLECORE_API FOptionalInventoryFiltersDTO : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInventoryFiltersDTO* Val;

	FOptionalInventoryFiltersDTO();

	explicit FOptionalInventoryFiltersDTO(UInventoryFiltersDTO* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};