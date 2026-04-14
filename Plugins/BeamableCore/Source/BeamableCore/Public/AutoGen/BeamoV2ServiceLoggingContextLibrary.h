#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceLoggingContext.h"

#include "BeamoV2ServiceLoggingContextLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceLoggingContextLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceLoggingContext To JSON String")
	static FString BeamoV2ServiceLoggingContextToJsonString(const UBeamoV2ServiceLoggingContext* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceLoggingContext", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Rules, Outer", NativeMakeFunc))
	static UBeamoV2ServiceLoggingContext* Make(FString ServiceName, FString RoutingKey, EBeamBeamoV2LogLevel DefaultLogLevel, FOptionalString Id, FOptionalArrayOfBeamoV2LogContextRule Rules, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceLoggingContext", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceLoggingContext* Serializable, FString& ServiceName, FString& RoutingKey, EBeamBeamoV2LogLevel& DefaultLogLevel, FOptionalString& Id, FOptionalArrayOfBeamoV2LogContextRule& Rules);
};