#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ThirdPartyAssociation.h"

#include "OptionalArrayOfThirdPartyAssociation.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfThirdPartyAssociationLibrary.MakeOptional", BeamOptionalType="TArray<UThirdPartyAssociation*>"))
struct BEAMABLECORE_API FOptionalArrayOfThirdPartyAssociation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UThirdPartyAssociation*> Val;

	FOptionalArrayOfThirdPartyAssociation();

	explicit FOptionalArrayOfThirdPartyAssociation(TArray<UThirdPartyAssociation*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};