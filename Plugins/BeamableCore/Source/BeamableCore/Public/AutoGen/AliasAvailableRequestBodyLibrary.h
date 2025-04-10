#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AliasAvailableRequestBody.h"

#include "AliasAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAliasAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|4 - Json", DisplayName="AliasAvailableRequestBody To JSON String")
	static FString AliasAvailableRequestBodyToJsonString(const UAliasAvailableRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|3 - Backend", DisplayName="Make AliasAvailableRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAliasAvailableRequestBody* Make(FString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|3 - Backend", DisplayName="Break AliasAvailableRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAliasAvailableRequestBody* Serializable, FString& Alias);
};