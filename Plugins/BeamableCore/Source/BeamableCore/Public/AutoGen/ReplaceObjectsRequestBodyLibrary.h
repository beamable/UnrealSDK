#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ReplaceObjectsRequestBody.h"

#include "ReplaceObjectsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UReplaceObjectsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="ReplaceObjectsRequestBody To JSON String")
	static FString ReplaceObjectsRequestBodyToJsonString(const UReplaceObjectsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make ReplaceObjectsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UReplaceObjectsRequestBody* Make(int64 SourcePlayerId, int64 TargetPlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break ReplaceObjectsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UReplaceObjectsRequestBody* Serializable, int64& SourcePlayerId, int64& TargetPlayerId);
};