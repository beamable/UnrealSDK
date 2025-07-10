#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/TestNotificationRequestArgs.h"

#include "TestNotificationRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UTestNotificationRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Json", DisplayName="TestNotificationRequestArgs To JSON String")
	static FString TestNotificationRequestArgsToJsonString(const UTestNotificationRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Make TestNotificationRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTestNotificationRequestArgs* Make(FString A, FString B, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Break TestNotificationRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UTestNotificationRequestArgs* Serializable, FString& A, FString& B);
};