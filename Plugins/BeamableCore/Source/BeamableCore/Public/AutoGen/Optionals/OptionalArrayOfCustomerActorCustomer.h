#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/CustomerActorCustomer.h"

#include "OptionalArrayOfCustomerActorCustomer.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfCustomerActorCustomerLibrary.MakeOptional", BeamOptionalType="TArray<UCustomerActorCustomer*>"))
struct BEAMABLECORE_API FOptionalArrayOfCustomerActorCustomer : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UCustomerActorCustomer*> Val;

	FOptionalArrayOfCustomerActorCustomer();

	explicit FOptionalArrayOfCustomerActorCustomer(TArray<UCustomerActorCustomer*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};