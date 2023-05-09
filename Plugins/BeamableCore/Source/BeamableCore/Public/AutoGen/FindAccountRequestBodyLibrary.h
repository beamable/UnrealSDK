#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FindAccountRequestBody.h"

#include "FindAccountRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFindAccountRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - FindAccountRequestBody To JSON String")
	static FString FindAccountRequestBodyToJsonString(const UFindAccountRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make FindAccountRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFindAccountRequestBody* Make(FString Query, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break FindAccountRequestBody", meta=(NativeBreakFunc))
	static void Break(const UFindAccountRequestBody* Serializable, FString& Query);
};