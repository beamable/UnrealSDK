#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateElevatedAccountRequestBody.h"

#include "CreateElevatedAccountRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateElevatedAccountRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="CreateElevatedAccountRequestBody To JSON String")
	static FString CreateElevatedAccountRequestBodyToJsonString(const UCreateElevatedAccountRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make CreateElevatedAccountRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Role, InitProperties, Outer", NativeMakeFunc))
	static UCreateElevatedAccountRequestBody* Make(FString Email, FOptionalString Role, FOptionalMapOfString InitProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break CreateElevatedAccountRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreateElevatedAccountRequestBody* Serializable, FString& Email, FOptionalString& Role, FOptionalMapOfString& InitProperties);
};