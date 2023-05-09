#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RepeatManifestRequestBody.h"

#include "RepeatManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URepeatManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RepeatManifestRequestBody To JSON String")
	static FString RepeatManifestRequestBodyToJsonString(const URepeatManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RepeatManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URepeatManifestRequestBody* Make(FString Uid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RepeatManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const URepeatManifestRequestBody* Serializable, FString& Uid);
};