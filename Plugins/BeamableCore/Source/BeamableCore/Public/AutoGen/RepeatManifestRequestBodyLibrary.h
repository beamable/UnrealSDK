#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RepeatManifestRequestBody.h"

#include "RepeatManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URepeatManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="RepeatManifestRequestBody To JSON String")
	static FString RepeatManifestRequestBodyToJsonString(const URepeatManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make RepeatManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URepeatManifestRequestBody* Make(FString Uid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break RepeatManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const URepeatManifestRequestBody* Serializable, FString& Uid);
};