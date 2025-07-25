#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/TokenResponse.h"

#include "OptionalTokenResponse.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalTokenResponseLibrary.MakeOptional", BeamOptionalType="UTokenResponse*"))
struct BEAMABLECORE_API FOptionalTokenResponse : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTokenResponse* Val;

	FOptionalTokenResponse();

	explicit FOptionalTokenResponse(UTokenResponse* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};