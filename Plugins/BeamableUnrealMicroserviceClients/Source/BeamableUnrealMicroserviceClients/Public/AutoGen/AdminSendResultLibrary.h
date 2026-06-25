#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AdminSendResult.h"

#include "AdminSendResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UAdminSendResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="AdminSendResult To JSON String")
	static FString AdminSendResultToJsonString(const UAdminSendResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make AdminSendResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAdminSendResult* Make(int32 Attempted, int32 Succeeded, int32 Failed, bool bSuccess, TArray<FString> Messages, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break AdminSendResult", meta=(NativeBreakFunc))
	static void Break(const UAdminSendResult* Serializable, int32& Attempted, int32& Succeeded, int32& Failed, bool& bSuccess, TArray<FString>& Messages);
};