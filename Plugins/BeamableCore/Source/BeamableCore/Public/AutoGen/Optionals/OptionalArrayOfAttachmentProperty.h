#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AttachmentProperty.h"

#include "OptionalArrayOfAttachmentProperty.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfAttachmentPropertyLibrary.MakeOptional", BeamOptionalType="TArray<UAttachmentProperty*>"))
struct BEAMABLECORE_API FOptionalArrayOfAttachmentProperty : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UAttachmentProperty*> Val;

	FOptionalArrayOfAttachmentProperty();

	explicit FOptionalArrayOfAttachmentProperty(TArray<UAttachmentProperty*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};