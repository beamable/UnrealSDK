#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AttachmentRequestBody.h"

#include "OptionalArrayOfAttachmentRequestBody.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfAttachmentRequestBodyLibrary.MakeOptional", BeamOptionalType="TArray<UAttachmentRequestBody*>"))
struct BEAMABLECORE_API FOptionalArrayOfAttachmentRequestBody : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<UAttachmentRequestBody*> Val;

	FOptionalArrayOfAttachmentRequestBody();

	explicit FOptionalArrayOfAttachmentRequestBody(TArray<UAttachmentRequestBody*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};