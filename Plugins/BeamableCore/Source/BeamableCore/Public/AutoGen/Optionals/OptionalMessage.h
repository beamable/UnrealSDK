#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Message.h"

#include "OptionalMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMessageLibrary.MakeOptional", BeamOptionalType="UMessage*"))
struct BEAMABLECORE_API FOptionalMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMessage* Val;

	FOptionalMessage();

	explicit FOptionalMessage(UMessage* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};