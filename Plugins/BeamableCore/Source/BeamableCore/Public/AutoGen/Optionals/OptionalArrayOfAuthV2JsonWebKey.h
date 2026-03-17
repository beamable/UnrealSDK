#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AuthV2JsonWebKey.h"

#include "OptionalArrayOfAuthV2JsonWebKey.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfAuthV2JsonWebKeyLibrary.MakeOptional", BeamOptionalType="TArray<UAuthV2JsonWebKey*>"))
struct BEAMABLECORE_API FOptionalArrayOfAuthV2JsonWebKey : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UAuthV2JsonWebKey*> Val;

	FOptionalArrayOfAuthV2JsonWebKey();

	explicit FOptionalArrayOfAuthV2JsonWebKey(TArray<UAuthV2JsonWebKey*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};