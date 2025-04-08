#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LambdaResponse.h"

#include "LambdaResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULambdaResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="LambdaResponse To JSON String")
	static FString LambdaResponseToJsonString(const ULambdaResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make LambdaResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Outer", NativeMakeFunc))
	static ULambdaResponse* Make(int32 StatusCode, FOptionalString Body, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break LambdaResponse", meta=(NativeBreakFunc))
	static void Break(const ULambdaResponse* Serializable, int32& StatusCode, FOptionalString& Body);
};