#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateLaunchMessageRequestBody.h"

#include "CreateLaunchMessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateLaunchMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="CreateLaunchMessageRequestBody To JSON String")
	static FString CreateLaunchMessageRequestBodyToJsonString(const UCreateLaunchMessageRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make CreateLaunchMessageRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCreateLaunchMessageRequestBody* Make(FString Name, FString Body, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break CreateLaunchMessageRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreateLaunchMessageRequestBody* Serializable, FString& Name, FString& Body);
};