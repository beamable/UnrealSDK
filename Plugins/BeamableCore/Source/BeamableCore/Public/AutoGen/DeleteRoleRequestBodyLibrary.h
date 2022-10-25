
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/DeleteRoleRequestBody.h"

#include "DeleteRoleRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteRoleRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DeleteRoleRequestBody To JSON String")
	static FString DeleteRoleRequestBodyToJsonString(const UDeleteRoleRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DeleteRoleRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeleteRoleRequestBody* Make(FString Realm, FString Role, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DeleteRoleRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeleteRoleRequestBody* Serializable, FString& Realm, FString& Role);
};