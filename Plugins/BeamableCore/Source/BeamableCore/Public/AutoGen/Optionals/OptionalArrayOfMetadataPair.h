#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/MetadataPair.h"

#include "OptionalArrayOfMetadataPair.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfMetadataPairLibrary.MakeOptional", BeamOptionalType="TArray<UMetadataPair*>"))
struct BEAMABLECORE_API FOptionalArrayOfMetadataPair : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UMetadataPair*> Val;

	FOptionalArrayOfMetadataPair();

	explicit FOptionalArrayOfMetadataPair(TArray<UMetadataPair*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};