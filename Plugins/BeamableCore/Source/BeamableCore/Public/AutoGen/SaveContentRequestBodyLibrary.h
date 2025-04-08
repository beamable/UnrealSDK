#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveContentRequestBody.h"

#include "SaveContentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveContentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="SaveContentRequestBody To JSON String")
	static FString SaveContentRequestBodyToJsonString(const USaveContentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make SaveContentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveContentRequestBody* Make(TArray<UContentDefinition*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break SaveContentRequestBody", meta=(NativeBreakFunc))
	static void Break(const USaveContentRequestBody* Serializable, TArray<UContentDefinition*>& Content);
};