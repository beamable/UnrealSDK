#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AccountsObjectInFlightMessage.h"

#include "OptionalArrayOfAccountsObjectInFlightMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfAccountsObjectInFlightMessageLibrary.MakeOptional", BeamOptionalType="TArray<UAccountsObjectInFlightMessage*>"))
struct BEAMABLECORE_API FOptionalArrayOfAccountsObjectInFlightMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UAccountsObjectInFlightMessage*> Val;

	FOptionalArrayOfAccountsObjectInFlightMessage();

	explicit FOptionalArrayOfAccountsObjectInFlightMessage(TArray<UAccountsObjectInFlightMessage*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};