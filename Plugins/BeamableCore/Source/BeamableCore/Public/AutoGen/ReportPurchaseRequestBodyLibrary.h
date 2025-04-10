#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ReportPurchaseRequestBody.h"

#include "ReportPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UReportPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="ReportPurchaseRequestBody To JSON String")
	static FString ReportPurchaseRequestBodyToJsonString(const UReportPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make ReportPurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bFree, Outer", NativeMakeFunc))
	static UReportPurchaseRequestBody* Make(FString ListingId, FOptionalBool bFree, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break ReportPurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UReportPurchaseRequestBody* Serializable, FString& ListingId, FOptionalBool& bFree);
};