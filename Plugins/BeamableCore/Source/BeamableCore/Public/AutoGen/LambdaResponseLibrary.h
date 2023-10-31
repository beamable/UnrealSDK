#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LambdaResponse.h"

#include "LambdaResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULambdaResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LambdaResponse To JSON String")
	static FString LambdaResponseToJsonString(const ULambdaResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LambdaResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Outer", NativeMakeFunc))
	static ULambdaResponse* Make(int32 StatusCode, FOptionalString Body, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LambdaResponse", meta=(NativeBreakFunc))
	static void Break(const ULambdaResponse* Serializable, int32& StatusCode, FOptionalString& Body);
};