#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ProblemDetails.h"

#include "ProblemDetailsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UProblemDetailsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ProblemDetails To JSON String")
	static FString ProblemDetailsToJsonString(const UProblemDetails* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ProblemDetails", meta=(DefaultToSelf="Outer", AdvancedDisplay="Type, Title, Status, Detail, Instance, Outer", NativeMakeFunc))
	static UProblemDetails* Make(FOptionalString Type, FOptionalString Title, FOptionalInt32 Status, FOptionalString Detail, FOptionalString Instance, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ProblemDetails", meta=(NativeBreakFunc))
	static void Break(const UProblemDetails* Serializable, FOptionalString& Type, FOptionalString& Title, FOptionalInt32& Status, FOptionalString& Detail, FOptionalString& Instance);
};