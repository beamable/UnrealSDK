#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Ticket.h"

#include "OptionalArrayOfTicket.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfTicketLibrary.MakeOptional", BeamOptionalType="TArray<UTicket*>"))
struct BEAMABLECORE_API FOptionalArrayOfTicket : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UTicket*> Val;

	FOptionalArrayOfTicket();

	explicit FOptionalArrayOfTicket(TArray<UTicket*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};