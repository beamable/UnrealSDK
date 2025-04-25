#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveSKUsRequestBody.h"

#include "SaveSKUsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveSKUsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="SaveSKUsRequestBody To JSON String")
	static FString SaveSKUsRequestBodyToJsonString(const USaveSKUsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make SaveSKUsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveSKUsRequestBody* Make(TArray<USKU*> Definitions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break SaveSKUsRequestBody", meta=(NativeBreakFunc))
	static void Break(const USaveSKUsRequestBody* Serializable, TArray<USKU*>& Definitions);
};