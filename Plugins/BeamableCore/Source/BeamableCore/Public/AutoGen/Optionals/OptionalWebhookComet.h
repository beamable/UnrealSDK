#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/WebhookComet.h"

#include "OptionalWebhookComet.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalWebhookCometLibrary.MakeOptional", BeamOptionalType="UWebhookComet*"))
struct BEAMABLECORE_API FOptionalWebhookComet : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	UWebhookComet* Val;

	FOptionalWebhookComet();

	explicit FOptionalWebhookComet(UWebhookComet* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};