#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetExactManifestRequestBody.h"

#include "GetExactManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetExactManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetExactManifestRequestBody To JSON String")
	static FString GetExactManifestRequestBodyToJsonString(const UGetExactManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetExactManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetExactManifestRequestBody* Make(FString Uid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetExactManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetExactManifestRequestBody* Serializable, FString& Uid);
};