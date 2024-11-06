#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/FederationInfo.h"

#include "OptionalFederationInfo.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalFederationInfoLibrary.MakeOptional", BeamOptionalType="UFederationInfo*"))
struct BEAMABLECORE_API FOptionalFederationInfo : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UFederationInfo* Val;

	FOptionalFederationInfo();

	explicit FOptionalFederationInfo(UFederationInfo* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};