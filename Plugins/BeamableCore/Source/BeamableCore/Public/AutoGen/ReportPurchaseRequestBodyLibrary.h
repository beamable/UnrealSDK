
#pragma once

#include "CoreMinimal.h"
#include "ReportPurchaseRequestBody.h"

#include "ReportPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UReportPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ReportPurchaseRequestBody To JSON String")
	static FString ReportPurchaseRequestBodyToJsonString(const UReportPurchaseRequestBody* Serializable, const bool Pretty);		
};