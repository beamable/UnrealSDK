#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoActorManifest.h"

#include "OptionalArrayOfBeamoActorManifest.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoActorManifestLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoActorManifest*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoActorManifest : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoActorManifest*> Val;

	FOptionalArrayOfBeamoActorManifest();

	explicit FOptionalArrayOfBeamoActorManifest(TArray<UBeamoActorManifest*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};