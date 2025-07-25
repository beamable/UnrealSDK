#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AccountsBasicAccount.h"

#include "OptionalAccountsBasicAccount.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalAccountsBasicAccountLibrary.MakeOptional", BeamOptionalType="UAccountsBasicAccount*"))
struct BEAMABLECORE_API FOptionalAccountsBasicAccount : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAccountsBasicAccount* Val;

	FOptionalAccountsBasicAccount();

	explicit FOptionalAccountsBasicAccount(UAccountsBasicAccount* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};