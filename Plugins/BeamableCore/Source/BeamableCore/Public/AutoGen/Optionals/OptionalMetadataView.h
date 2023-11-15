#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/MetadataView.h"

#include "OptionalMetadataView.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMetadataViewLibrary.MakeOptional", BeamOptionalType="UMetadataView*"))
struct BEAMABLECORE_API FOptionalMetadataView : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMetadataView* Val;

	FOptionalMetadataView();

	explicit FOptionalMetadataView(UMetadataView* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};