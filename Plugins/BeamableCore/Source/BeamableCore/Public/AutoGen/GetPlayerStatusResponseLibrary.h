#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetPlayerStatusResponse.h"

#include "GetPlayerStatusResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetPlayerStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetPlayerStatusResponse To JSON String")
	static FString GetPlayerStatusResponseToJsonString(const UGetPlayerStatusResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetPlayerStatusResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetPlayerStatusResponse* Make(TArray<UPlayerStatus*> Statuses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetPlayerStatusResponse", meta=(NativeBreakFunc))
	static void Break(const UGetPlayerStatusResponse* Serializable, TArray<UPlayerStatus*>& Statuses);
};