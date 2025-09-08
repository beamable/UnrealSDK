#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AccountsBasicInFlightMessage.h"

#include "OptionalArrayOfAccountsBasicInFlightMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfAccountsBasicInFlightMessageLibrary.MakeOptional", BeamOptionalType="TArray<UAccountsBasicInFlightMessage*>"))
struct BEAMABLECORE_API FOptionalArrayOfAccountsBasicInFlightMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UAccountsBasicInFlightMessage*> Val;

	FOptionalArrayOfAccountsBasicInFlightMessage();

	explicit FOptionalArrayOfAccountsBasicInFlightMessage(TArray<UAccountsBasicInFlightMessage*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};