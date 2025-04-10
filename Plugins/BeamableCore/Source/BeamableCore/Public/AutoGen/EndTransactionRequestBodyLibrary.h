#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EndTransactionRequestBody.h"

#include "EndTransactionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEndTransactionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|4 - Json", DisplayName="EndTransactionRequestBody To JSON String")
	static FString EndTransactionRequestBodyToJsonString(const UEndTransactionRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|3 - Backend", DisplayName="Make EndTransactionRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEndTransactionRequestBody* Make(FString Transaction, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|3 - Backend", DisplayName="Break EndTransactionRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEndTransactionRequestBody* Serializable, FString& Transaction);
};