
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/UnarchiveProjectRequestBody.h"

#include "UnarchiveProjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUnarchiveProjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UnarchiveProjectRequestBody To JSON String")
	static FString UnarchiveProjectRequestBodyToJsonString(const UUnarchiveProjectRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UnarchiveProjectRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UUnarchiveProjectRequestBody* Make(FString ProjectId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UnarchiveProjectRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUnarchiveProjectRequestBody* Serializable, FString& ProjectId);
};