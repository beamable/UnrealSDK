#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceTemplateView.h"

#include "OptionalArrayOfBeamoV2ServiceTemplateView.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceTemplateViewLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceTemplateView*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceTemplateView : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceTemplateView*> Val;

	FOptionalArrayOfBeamoV2ServiceTemplateView();

	explicit FOptionalArrayOfBeamoV2ServiceTemplateView(TArray<UBeamoV2ServiceTemplateView*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};