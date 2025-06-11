#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UpgradeItemRequestArgs.h"

#include "UpgradeItemRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UUpgradeItemRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Json", DisplayName="UpgradeItemRequestArgs To JSON String")
	static FString UpgradeItemRequestArgsToJsonString(const UUpgradeItemRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make UpgradeItemRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UUpgradeItemRequestArgs* Make(int64 GamerTag, int64 ItemInstaceID, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Break UpgradeItemRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UUpgradeItemRequestArgs* Serializable, int64& GamerTag, int64& ItemInstaceID);
};