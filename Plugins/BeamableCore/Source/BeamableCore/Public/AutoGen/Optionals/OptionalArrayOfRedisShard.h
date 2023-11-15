#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RedisShard.h"

#include "OptionalArrayOfRedisShard.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfRedisShardLibrary.MakeOptional", BeamOptionalType="TArray<URedisShard*>"))
struct BEAMABLECORE_API FOptionalArrayOfRedisShard : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<URedisShard*> Val;

	FOptionalArrayOfRedisShard();

	explicit FOptionalArrayOfRedisShard(TArray<URedisShard*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};