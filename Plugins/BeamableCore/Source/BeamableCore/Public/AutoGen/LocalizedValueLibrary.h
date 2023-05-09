#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LocalizedValue.h"

#include "LocalizedValueLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULocalizedValueLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LocalizedValue To JSON String")
	static FString LocalizedValueToJsonString(const ULocalizedValue* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LocalizedValue", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULocalizedValue* Make(FString Language, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LocalizedValue", meta=(NativeBreakFunc))
	static void Break(const ULocalizedValue* Serializable, FString& Language, FString& Value);
};