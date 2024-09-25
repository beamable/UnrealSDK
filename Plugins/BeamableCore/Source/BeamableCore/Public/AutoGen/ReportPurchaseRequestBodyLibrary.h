#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/ReportPurchaseRequestBody.h"

#include "ReportPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UReportPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ReportPurchaseRequestBody To JSON String")
	static FString ReportPurchaseRequestBodyToJsonString(const UReportPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ReportPurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bFree, Outer", NativeMakeFunc))
	static UReportPurchaseRequestBody* Make(FString ListingId, FOptionalBool bFree, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ReportPurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UReportPurchaseRequestBody* Serializable, FString& ListingId, FOptionalBool& bFree);
};