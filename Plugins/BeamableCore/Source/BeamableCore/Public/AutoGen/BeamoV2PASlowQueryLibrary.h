#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2PASlowQuery.h"

#include "BeamoV2PASlowQueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2PASlowQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2PASlowQuery To JSON String")
	static FString BeamoV2PASlowQueryToJsonString(const UBeamoV2PASlowQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2PASlowQuery", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoV2PASlowQuery* Make(FString Line, FString Namespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2PASlowQuery", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2PASlowQuery* Serializable, FString& Line, FString& Namespace);
};