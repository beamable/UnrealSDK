#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/AdminGetPlayerStatusResponse.h"

#include "AdminGetPlayerStatusResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAdminGetPlayerStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AdminGetPlayerStatusResponse To JSON String")
	static FString AdminGetPlayerStatusResponseToJsonString(const UAdminGetPlayerStatusResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AdminGetPlayerStatusResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAdminGetPlayerStatusResponse* Make(TArray<UAdminPlayerStatus*> Statuses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AdminGetPlayerStatusResponse", meta=(NativeBreakFunc))
	static void Break(const UAdminGetPlayerStatusResponse* Serializable, TArray<UAdminPlayerStatus*>& Statuses);
};