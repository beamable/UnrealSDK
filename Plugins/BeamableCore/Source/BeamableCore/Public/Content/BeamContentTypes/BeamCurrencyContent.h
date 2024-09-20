#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/ReplacementTypes/BeamClientPermission.h"
#include "BeamBackend/ReplacementTypes/BeamFederation.h"
#include "Content/BeamContentObject.h"

#include "BeamCurrencyContent.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamCurrencyContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamCurrencyContent(FString& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamClientPermission clientPermission;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	int64 startingAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Federation",Category="Beam")
	FOptionalBeamFederation external;
};

DEFINE_CONTENT_TYPE_NAME(UBeamCurrencyContent, "currency")
