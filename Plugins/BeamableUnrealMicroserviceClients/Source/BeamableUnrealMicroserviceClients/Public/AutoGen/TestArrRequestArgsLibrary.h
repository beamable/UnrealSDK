#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/TestArrRequestArgs.h"

#include "TestArrRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UTestArrRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Json", DisplayName="TestArrRequestArgs To JSON String")
	static FString TestArrRequestArgsToJsonString(const UTestArrRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Make TestArrRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTestArrRequestArgs* Make(int32 A, int32 B, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Break TestArrRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UTestArrRequestArgs* Serializable, int32& A, int32& B);
};