#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MyCoolNotification.h"

#include "MyCoolNotificationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMyCoolNotificationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Json", DisplayName="MyCoolNotification To JSON String")
	static FString MyCoolNotificationToJsonString(const UMyCoolNotification* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Make MyCoolNotification", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMyCoolNotification* Make(FString FieldA, FString FieldB, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Break MyCoolNotification", meta=(NativeBreakFunc))
	static void Break(const UMyCoolNotification* Serializable, FString& FieldA, FString& FieldB);
};