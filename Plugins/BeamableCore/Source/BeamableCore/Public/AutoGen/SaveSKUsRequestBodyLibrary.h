#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveSKUsRequestBody.h"

#include "SaveSKUsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveSKUsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SaveSKUsRequestBody To JSON String")
	static FString SaveSKUsRequestBodyToJsonString(const USaveSKUsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SaveSKUsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveSKUsRequestBody* Make(TArray<USKU*> Definitions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SaveSKUsRequestBody", meta=(NativeBreakFunc))
	static void Break(const USaveSKUsRequestBody* Serializable, TArray<USKU*>& Definitions);
};