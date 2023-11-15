#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/DonationRequestBody.h"

#include "OptionalMapOfDonationRequestBody.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMapOfDonationRequestBodyLibrary.MakeOptional", BeamOptionalType="TMap<FString, UDonationRequestBody*>"))
struct BEAMABLECORE_API FOptionalMapOfDonationRequestBody : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, UDonationRequestBody*> Val;

	FOptionalMapOfDonationRequestBody();

	explicit FOptionalMapOfDonationRequestBody(TMap<FString, UDonationRequestBody*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};