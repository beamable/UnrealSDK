#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Era.h"

#include "EraLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEraLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Era To JSON String")
	static FString EraToJsonString(const UEra* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Era", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEra* Make(int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Era", meta=(NativeBreakFunc))
	static void Break(const UEra* Serializable, int32& Value);
};