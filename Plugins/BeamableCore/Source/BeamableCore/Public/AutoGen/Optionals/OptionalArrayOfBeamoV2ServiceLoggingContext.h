#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceLoggingContext.h"

#include "OptionalArrayOfBeamoV2ServiceLoggingContext.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceLoggingContextLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceLoggingContext*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceLoggingContext : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceLoggingContext*> Val;

	FOptionalArrayOfBeamoV2ServiceLoggingContext();

	explicit FOptionalArrayOfBeamoV2ServiceLoggingContext(TArray<UBeamoV2ServiceLoggingContext*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};