#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundTestArrResponse.h"

#include "MSPlaygroundTestArrResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMSPlaygroundTestArrResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Json", DisplayName="MSPlaygroundTestArrResponse To JSON String")
	static FString MSPlaygroundTestArrResponseToJsonString(const UMSPlaygroundTestArrResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Make MSPlaygroundTestArrResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMSPlaygroundTestArrResponse* Make(TArray<int32> Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Break MSPlaygroundTestArrResponse", meta=(NativeBreakFunc))
	static void Break(const UMSPlaygroundTestArrResponse* Serializable, TArray<int32>& Value);
};