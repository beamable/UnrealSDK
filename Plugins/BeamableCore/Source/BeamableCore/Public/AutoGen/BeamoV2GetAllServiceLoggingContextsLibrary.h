#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetAllServiceLoggingContexts.h"

#include "BeamoV2GetAllServiceLoggingContextsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2GetAllServiceLoggingContextsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2GetAllServiceLoggingContexts To JSON String")
	static FString BeamoV2GetAllServiceLoggingContextsToJsonString(const UBeamoV2GetAllServiceLoggingContexts* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2GetAllServiceLoggingContexts", meta=(DefaultToSelf="Outer", AdvancedDisplay="Contexts, Outer", NativeMakeFunc))
	static UBeamoV2GetAllServiceLoggingContexts* Make(FOptionalArrayOfBeamoV2ServiceLoggingContext Contexts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2GetAllServiceLoggingContexts", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2GetAllServiceLoggingContexts* Serializable, FOptionalArrayOfBeamoV2ServiceLoggingContext& Contexts);
};