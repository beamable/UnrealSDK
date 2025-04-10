#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ProblemDetails.h"

#include "ProblemDetailsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UProblemDetailsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="ProblemDetails To JSON String")
	static FString ProblemDetailsToJsonString(const UProblemDetails* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make ProblemDetails", meta=(DefaultToSelf="Outer", AdvancedDisplay="Type, Title, Status, Detail, Instance, Outer", NativeMakeFunc))
	static UProblemDetails* Make(FOptionalString Type, FOptionalString Title, FOptionalInt32 Status, FOptionalString Detail, FOptionalString Instance, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break ProblemDetails", meta=(NativeBreakFunc))
	static void Break(const UProblemDetails* Serializable, FOptionalString& Type, FOptionalString& Title, FOptionalInt32& Status, FOptionalString& Detail, FOptionalString& Instance);
};