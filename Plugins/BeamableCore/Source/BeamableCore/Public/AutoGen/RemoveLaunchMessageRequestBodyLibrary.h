#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RemoveLaunchMessageRequestBody.h"

#include "RemoveLaunchMessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URemoveLaunchMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RemoveLaunchMessageRequestBody To JSON String")
	static FString RemoveLaunchMessageRequestBodyToJsonString(const URemoveLaunchMessageRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RemoveLaunchMessageRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URemoveLaunchMessageRequestBody* Make(FString File, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RemoveLaunchMessageRequestBody", meta=(NativeBreakFunc))
	static void Break(const URemoveLaunchMessageRequestBody* Serializable, FString& File);
};