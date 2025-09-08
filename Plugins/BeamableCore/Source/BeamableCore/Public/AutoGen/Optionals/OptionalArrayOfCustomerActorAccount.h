#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/CustomerActorAccount.h"

#include "OptionalArrayOfCustomerActorAccount.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfCustomerActorAccountLibrary.MakeOptional", BeamOptionalType="TArray<UCustomerActorAccount*>"))
struct BEAMABLECORE_API FOptionalArrayOfCustomerActorAccount : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UCustomerActorAccount*> Val;

	FOptionalArrayOfCustomerActorAccount();

	explicit FOptionalArrayOfCustomerActorAccount(TArray<UCustomerActorAccount*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};