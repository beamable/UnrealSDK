#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EndTransactionRequestBody.h"

#include "EndTransactionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEndTransactionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EndTransactionRequestBody To JSON String")
	static FString EndTransactionRequestBodyToJsonString(const UEndTransactionRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EndTransactionRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEndTransactionRequestBody* Make(FString Transaction, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EndTransactionRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEndTransactionRequestBody* Serializable, FString& Transaction);
};