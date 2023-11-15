#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"

#include "OptionalArrayOfOnlineStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfOnlineStatusLibrary.MakeOptional", BeamOptionalType="TArray<UOnlineStatus*>"))
struct BEAMABLECORE_API FOptionalArrayOfOnlineStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UOnlineStatus*> Val;

	FOptionalArrayOfOnlineStatus();

	explicit FOptionalArrayOfOnlineStatus(TArray<UOnlineStatus*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};