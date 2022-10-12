
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/Catalog.h"

#include "OptionalCatalog.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalCatalogLibrary.MakeOptionalCatalog"))
struct FOptionalCatalog : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UCatalog* Val;

	FOptionalCatalog();

	explicit FOptionalCatalog(UCatalog* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};