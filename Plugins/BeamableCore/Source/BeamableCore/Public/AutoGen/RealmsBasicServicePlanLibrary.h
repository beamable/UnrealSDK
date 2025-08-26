#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicServicePlan.h"

#include "RealmsBasicServicePlanLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicServicePlanLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicServicePlan To JSON String")
	static FString RealmsBasicServicePlanToJsonString(const URealmsBasicServicePlan* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicServicePlan", meta=(DefaultToSelf="Outer", AdvancedDisplay="MinCustomerStatusSaved, Limits, Created, Outer", NativeMakeFunc))
	static URealmsBasicServicePlan* Make(FString Name, URealmsBasicDataDomain* DataDomain, FOptionalString MinCustomerStatusSaved, FOptionalRealmsBasicServiceLimits Limits, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicServicePlan", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicServicePlan* Serializable, FString& Name, URealmsBasicDataDomain*& DataDomain, FOptionalString& MinCustomerStatusSaved, FOptionalRealmsBasicServiceLimits& Limits, FOptionalInt64& Created);
};