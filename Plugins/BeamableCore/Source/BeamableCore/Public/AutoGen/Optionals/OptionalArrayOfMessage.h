#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Message.h"

#include "OptionalArrayOfMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfMessageLibrary.MakeOptional", BeamOptionalType="TArray<UMessage*>"))
struct BEAMABLECORE_API FOptionalArrayOfMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UMessage*> Val;

	FOptionalArrayOfMessage();

	explicit FOptionalArrayOfMessage(TArray<UMessage*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};