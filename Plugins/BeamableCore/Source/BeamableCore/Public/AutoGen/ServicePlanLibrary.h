#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServicePlan.h"

#include "ServicePlanLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServicePlanLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServicePlan To JSON String")
	static FString ServicePlanToJsonString(const UServicePlan* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServicePlan", meta=(DefaultToSelf="Outer", AdvancedDisplay="MinCustomerStatusSaved, Limits, Created, Outer", NativeMakeFunc))
	static UServicePlan* Make(FString Name, UDataDomain* DataDomain, FOptionalString MinCustomerStatusSaved, FOptionalServiceLimits Limits, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServicePlan", meta=(NativeBreakFunc))
	static void Break(const UServicePlan* Serializable, FString& Name, UDataDomain*& DataDomain, FOptionalString& MinCustomerStatusSaved, FOptionalServiceLimits& Limits, FOptionalInt64& Created);
};