#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Catalog.h"

#include "OptionalCatalog.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalCatalogLibrary.MakeOptional", BeamOptionalType="UCatalog*"))
struct BEAMABLECORE_API FOptionalCatalog : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCatalog* Val;

	FOptionalCatalog();

	explicit FOptionalCatalog(UCatalog* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};