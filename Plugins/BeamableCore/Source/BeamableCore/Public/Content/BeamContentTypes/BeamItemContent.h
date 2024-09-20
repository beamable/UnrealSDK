#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/ReplacementTypes/BeamClientPermission.h"
#include "BeamBackend/ReplacementTypes/BeamFederation.h"
#include "Content/BeamContentObject.h"

#include "BeamItemContent.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamItemContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamItemContent(FString& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamClientPermission clientPermission;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Federation",Category="Beam")
	FOptionalBeamFederation external;
	
};

DEFINE_CONTENT_TYPE_NAME(UBeamItemContent, "items")