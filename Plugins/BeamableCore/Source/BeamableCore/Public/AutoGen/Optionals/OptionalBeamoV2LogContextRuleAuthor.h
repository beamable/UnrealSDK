#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRuleAuthor.h"

#include "OptionalBeamoV2LogContextRuleAuthor.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoV2LogContextRuleAuthorLibrary.MakeOptional", BeamOptionalType="UBeamoV2LogContextRuleAuthor*"))
struct BEAMABLECORE_API FOptionalBeamoV2LogContextRuleAuthor : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UBeamoV2LogContextRuleAuthor* Val;

	FOptionalBeamoV2LogContextRuleAuthor();

	explicit FOptionalBeamoV2LogContextRuleAuthor(UBeamoV2LogContextRuleAuthor* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};