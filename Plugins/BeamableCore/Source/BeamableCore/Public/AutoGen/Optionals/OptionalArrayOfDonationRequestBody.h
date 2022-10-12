
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/DonationRequestBody.h"

#include "OptionalArrayOfDonationRequestBody.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfDonationRequestBodyLibrary.MakeOptionalArrayOfDonationRequestBody"))
struct FOptionalArrayOfDonationRequestBody : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UDonationRequestBody*> Val;

	FOptionalArrayOfDonationRequestBody();

	explicit FOptionalArrayOfDonationRequestBody(TArray<UDonationRequestBody*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};