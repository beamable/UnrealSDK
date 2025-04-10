#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventApplyRequestBody.h"

#include "EventApplyRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventApplyRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventApplyRequestBody To JSON String")
	static FString EventApplyRequestBodyToJsonString(const UEventApplyRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventApplyRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventApplyRequestBody* Make(UEvent* Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventApplyRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEventApplyRequestBody* Serializable, UEvent*& Content);
};