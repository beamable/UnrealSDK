#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStatus.h"

#include "OptionalArrayOfBeamoV2ServiceStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceStatusLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceStatus*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceStatus*> Val;

	FOptionalArrayOfBeamoV2ServiceStatus();

	explicit FOptionalArrayOfBeamoV2ServiceStatus(TArray<UBeamoV2ServiceStatus*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};