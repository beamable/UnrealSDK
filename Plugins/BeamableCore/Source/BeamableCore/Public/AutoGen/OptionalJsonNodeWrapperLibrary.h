#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OptionalJsonNodeWrapper.h"

#include "OptionalJsonNodeWrapperLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOptionalJsonNodeWrapperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - OptionalJsonNodeWrapper To JSON String")
	static FString OptionalJsonNodeWrapperToJsonString(const UOptionalJsonNodeWrapper* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make OptionalJsonNodeWrapper", meta=(DefaultToSelf="Outer", AdvancedDisplay="Node, Outer", NativeMakeFunc))
	static UOptionalJsonNodeWrapper* Make(FOptionalString Node, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break OptionalJsonNodeWrapper", meta=(NativeBreakFunc))
	static void Break(const UOptionalJsonNodeWrapper* Serializable, FOptionalString& Node);
};