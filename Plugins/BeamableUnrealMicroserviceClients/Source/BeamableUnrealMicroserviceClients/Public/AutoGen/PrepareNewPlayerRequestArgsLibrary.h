#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PrepareNewPlayerRequestArgs.h"

#include "PrepareNewPlayerRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UPrepareNewPlayerRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PrepareNewPlayerRequestArgs To JSON String")
	static FString PrepareNewPlayerRequestArgsToJsonString(const UPrepareNewPlayerRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PrepareNewPlayerRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPrepareNewPlayerRequestArgs* Make(int64 UserID, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PrepareNewPlayerRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UPrepareNewPlayerRequestArgs* Serializable, int64& UserID);
};