#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PropertyDelta.h"

#include "PropertyDeltaLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPropertyDeltaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="PropertyDelta To JSON String")
	static FString PropertyDeltaToJsonString(const UPropertyDelta* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make PropertyDelta", meta=(DefaultToSelf="Outer", AdvancedDisplay="Before, After, Outer", NativeMakeFunc))
	static UPropertyDelta* Make(FOptionalString Before, FOptionalString After, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break PropertyDelta", meta=(NativeBreakFunc))
	static void Break(const UPropertyDelta* Serializable, FOptionalString& Before, FOptionalString& After);
};