
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/MailBasicMessage.h"

#include "OptionalMailBasicMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalMailBasicMessageLibrary.MakeOptional", BeamOptionalType="UMailBasicMessage*"))
struct BEAMABLECORE_API FOptionalMailBasicMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UMailBasicMessage* Val;

	FOptionalMailBasicMessage();

	explicit FOptionalMailBasicMessage(UMailBasicMessage* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};