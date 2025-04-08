#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatUpdateRequestBody.h"

#include "StatUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="StatUpdateRequestBody To JSON String")
	static FString StatUpdateRequestBodyToJsonString(const UStatUpdateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make StatUpdateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bEmitAnalytics, ObjectId, Set, Add, Outer", NativeMakeFunc))
	static UStatUpdateRequestBody* Make(FOptionalBool bEmitAnalytics, FOptionalBeamStatsType ObjectId, FOptionalMapOfString Set, FOptionalMapOfString Add, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break StatUpdateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStatUpdateRequestBody* Serializable, FOptionalBool& bEmitAnalytics, FOptionalBeamStatsType& ObjectId, FOptionalMapOfString& Set, FOptionalMapOfString& Add);
};