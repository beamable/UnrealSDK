#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStorageStatus.h"

#include "OptionalArrayOfBeamoV2ServiceStorageStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceStorageStatusLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceStorageStatus*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceStorageStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceStorageStatus*> Val;

	FOptionalArrayOfBeamoV2ServiceStorageStatus();

	explicit FOptionalArrayOfBeamoV2ServiceStorageStatus(TArray<UBeamoV2ServiceStorageStatus*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};