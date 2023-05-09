#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AddAccountRequestBody.h"

#include "AddAccountRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAddAccountRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AddAccountRequestBody To JSON String")
	static FString AddAccountRequestBodyToJsonString(const UAddAccountRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AddAccountRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Role, Outer", NativeMakeFunc))
	static UAddAccountRequestBody* Make(FString Email, FOptionalString Role, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AddAccountRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAddAccountRequestBody* Serializable, FString& Email, FOptionalString& Role);
};