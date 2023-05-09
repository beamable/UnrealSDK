#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/MailObjectMessage.h"

#include "OptionalArrayOfMailObjectMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfMailObjectMessageLibrary.MakeOptional", BeamOptionalType="TArray<UMailObjectMessage*>"))
struct BEAMABLECORE_API FOptionalArrayOfMailObjectMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UMailObjectMessage*> Val;

	FOptionalArrayOfMailObjectMessage();

	explicit FOptionalArrayOfMailObjectMessage(TArray<UMailObjectMessage*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};