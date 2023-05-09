#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableResponse.h"

#include "AccountAvailableResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountAvailableResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AccountAvailableResponse To JSON String")
	static FString AccountAvailableResponseToJsonString(const UAccountAvailableResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AccountAvailableResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAccountAvailableResponse* Make(bool bAvailable, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AccountAvailableResponse", meta=(NativeBreakFunc))
	static void Break(const UAccountAvailableResponse* Serializable, bool& bAvailable);
};