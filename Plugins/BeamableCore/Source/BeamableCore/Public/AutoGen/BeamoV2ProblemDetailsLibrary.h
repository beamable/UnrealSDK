#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ProblemDetails.h"

#include "BeamoV2ProblemDetailsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ProblemDetailsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ProblemDetails To JSON String")
	static FString BeamoV2ProblemDetailsToJsonString(const UBeamoV2ProblemDetails* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ProblemDetails", meta=(DefaultToSelf="Outer", AdvancedDisplay="Type, Title, Status, Detail, Instance, Outer", NativeMakeFunc))
	static UBeamoV2ProblemDetails* Make(FOptionalString Type, FOptionalString Title, FOptionalInt32 Status, FOptionalString Detail, FOptionalString Instance, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ProblemDetails", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ProblemDetails* Serializable, FOptionalString& Type, FOptionalString& Title, FOptionalInt32& Status, FOptionalString& Detail, FOptionalString& Instance);
};