#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ClearStatusRequestBody.h"

#include "ClearStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClearStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="ClearStatusRequestBody To JSON String")
	static FString ClearStatusRequestBodyToJsonString(const UClearStatusRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make ClearStatusRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UClearStatusRequestBody* Make(FString Store, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break ClearStatusRequestBody", meta=(NativeBreakFunc))
	static void Break(const UClearStatusRequestBody* Serializable, FString& Store);
};