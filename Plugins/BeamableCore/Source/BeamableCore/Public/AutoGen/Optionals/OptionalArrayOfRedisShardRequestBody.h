#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RedisShardRequestBody.h"

#include "OptionalArrayOfRedisShardRequestBody.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfRedisShardRequestBodyLibrary.MakeOptional", BeamOptionalType="TArray<URedisShardRequestBody*>"))
struct BEAMABLECORE_API FOptionalArrayOfRedisShardRequestBody : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<URedisShardRequestBody*> Val;

	FOptionalArrayOfRedisShardRequestBody();

	explicit FOptionalArrayOfRedisShardRequestBody(TArray<URedisShardRequestBody*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};