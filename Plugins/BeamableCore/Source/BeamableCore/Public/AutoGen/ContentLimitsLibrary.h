#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentLimits.h"

#include "ContentLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ContentLimits To JSON String")
	static FString ContentLimitsToJsonString(const UContentLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ContentLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="MaxDistinctContentIds, Outer", NativeMakeFunc))
	static UContentLimits* Make(FOptionalInt32 MaxDistinctContentIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ContentLimits", meta=(NativeBreakFunc))
	static void Break(const UContentLimits* Serializable, FOptionalInt32& MaxDistinctContentIds);
};