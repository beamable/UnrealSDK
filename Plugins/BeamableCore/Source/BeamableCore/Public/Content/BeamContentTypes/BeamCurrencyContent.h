#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/ReplacementTypes/BeamClientPermission.h"
#include "Content/BeamContentObject.h"

#include "BeamCurrencyContent.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamCurrencyContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamCurrencyContent(FString& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamClientPermission clientPermission;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 startingAmount;	
};

DEFINE_CONTENT_TYPE_NAME(UBeamCurrencyContent, "currency")