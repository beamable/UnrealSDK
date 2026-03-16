#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AuthV2RefreshTokenResponse.h"

#include "OptionalArrayOfAuthV2RefreshTokenResponse.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfAuthV2RefreshTokenResponseLibrary.MakeOptional", BeamOptionalType="TArray<UAuthV2RefreshTokenResponse*>"))
struct BEAMABLECORE_API FOptionalArrayOfAuthV2RefreshTokenResponse : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UAuthV2RefreshTokenResponse*> Val;

	FOptionalArrayOfAuthV2RefreshTokenResponse();

	explicit FOptionalArrayOfAuthV2RefreshTokenResponse(TArray<UAuthV2RefreshTokenResponse*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};