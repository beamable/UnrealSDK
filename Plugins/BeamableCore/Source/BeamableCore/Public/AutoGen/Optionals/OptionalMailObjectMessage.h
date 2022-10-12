
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/MailObjectMessage.h"

#include "OptionalMailObjectMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalMailObjectMessageLibrary.MakeOptionalMailObjectMessage"))
struct FOptionalMailObjectMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UMailObjectMessage* Val;

	FOptionalMailObjectMessage();

	explicit FOptionalMailObjectMessage(UMailObjectMessage* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};