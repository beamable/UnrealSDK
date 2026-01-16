#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/TransactionHistoryEntry.h"

#include "OptionalArrayOfTransactionHistoryEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfTransactionHistoryEntryLibrary.MakeOptional", BeamOptionalType="TArray<UTransactionHistoryEntry*>"))
struct BEAMABLECORE_API FOptionalArrayOfTransactionHistoryEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UTransactionHistoryEntry*> Val;

	FOptionalArrayOfTransactionHistoryEntry();

	explicit FOptionalArrayOfTransactionHistoryEntry(TArray<UTransactionHistoryEntry*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};