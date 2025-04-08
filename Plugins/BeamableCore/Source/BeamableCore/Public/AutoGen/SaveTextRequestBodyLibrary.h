#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveTextRequestBody.h"

#include "SaveTextRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveTextRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="SaveTextRequestBody To JSON String")
	static FString SaveTextRequestBodyToJsonString(const USaveTextRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make SaveTextRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveTextRequestBody* Make(TArray<UTextDefinition*> Text, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break SaveTextRequestBody", meta=(NativeBreakFunc))
	static void Break(const USaveTextRequestBody* Serializable, TArray<UTextDefinition*>& Text);
};