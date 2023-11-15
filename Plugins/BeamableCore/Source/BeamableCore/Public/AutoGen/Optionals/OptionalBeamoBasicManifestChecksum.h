#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoBasicManifestChecksum.h"

#include "OptionalBeamoBasicManifestChecksum.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoBasicManifestChecksumLibrary.MakeOptional", BeamOptionalType="UBeamoBasicManifestChecksum*"))
struct BEAMABLECORE_API FOptionalBeamoBasicManifestChecksum : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UBeamoBasicManifestChecksum* Val;

	FOptionalBeamoBasicManifestChecksum();

	explicit FOptionalBeamoBasicManifestChecksum(UBeamoBasicManifestChecksum* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};