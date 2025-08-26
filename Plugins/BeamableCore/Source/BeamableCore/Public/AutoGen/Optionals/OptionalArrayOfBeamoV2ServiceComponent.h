#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceComponent.h"

#include "OptionalArrayOfBeamoV2ServiceComponent.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceComponentLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceComponent*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceComponent : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceComponent*> Val;

	FOptionalArrayOfBeamoV2ServiceComponent();

	explicit FOptionalArrayOfBeamoV2ServiceComponent(TArray<UBeamoV2ServiceComponent*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};