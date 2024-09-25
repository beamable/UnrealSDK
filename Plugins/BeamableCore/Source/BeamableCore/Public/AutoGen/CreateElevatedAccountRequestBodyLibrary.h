#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/CreateElevatedAccountRequestBody.h"

#include "CreateElevatedAccountRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateElevatedAccountRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CreateElevatedAccountRequestBody To JSON String")
	static FString CreateElevatedAccountRequestBodyToJsonString(const UCreateElevatedAccountRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CreateElevatedAccountRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Role, InitProperties, Outer", NativeMakeFunc))
	static UCreateElevatedAccountRequestBody* Make(FString Email, FOptionalString Role, FOptionalMapOfString InitProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CreateElevatedAccountRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreateElevatedAccountRequestBody* Serializable, FString& Email, FOptionalString& Role, FOptionalMapOfString& InitProperties);
};