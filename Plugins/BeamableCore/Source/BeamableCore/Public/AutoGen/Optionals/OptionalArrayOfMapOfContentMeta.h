#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Maps/MapOfContentMeta.h"

#include "OptionalArrayOfMapOfContentMeta.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfMapOfContentMetaLibrary.MakeOptional", BeamOptionalType="TArray<FMapOfContentMeta>"))
struct BEAMABLECORE_API FOptionalArrayOfMapOfContentMeta : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FMapOfContentMeta> Val;

	FOptionalArrayOfMapOfContentMeta();

	explicit FOptionalArrayOfMapOfContentMeta(TArray<FMapOfContentMeta> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};