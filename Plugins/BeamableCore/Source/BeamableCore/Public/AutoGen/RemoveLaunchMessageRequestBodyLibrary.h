#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/RemoveLaunchMessageRequestBody.h"

#include "RemoveLaunchMessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URemoveLaunchMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RemoveLaunchMessageRequestBody To JSON String")
	static FString RemoveLaunchMessageRequestBodyToJsonString(const URemoveLaunchMessageRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RemoveLaunchMessageRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URemoveLaunchMessageRequestBody* Make(FString File, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RemoveLaunchMessageRequestBody", meta=(NativeBreakFunc))
	static void Break(const URemoveLaunchMessageRequestBody* Serializable, FString& File);
};