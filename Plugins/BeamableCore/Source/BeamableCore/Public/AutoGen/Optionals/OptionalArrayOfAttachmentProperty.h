
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/AttachmentProperty.h"

#include "OptionalArrayOfAttachmentProperty.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfAttachmentPropertyLibrary.MakeOptional"))
struct BEAMABLECORE_API FOptionalArrayOfAttachmentProperty : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UAttachmentProperty*> Val;

	FOptionalArrayOfAttachmentProperty();

	explicit FOptionalArrayOfAttachmentProperty(TArray<UAttachmentProperty*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};