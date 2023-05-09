#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsRequestBody.h"

#include "GetStatusForGroupsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStatusForGroupsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetStatusForGroupsRequestBody To JSON String")
	static FString GetStatusForGroupsRequestBodyToJsonString(const UGetStatusForGroupsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetStatusForGroupsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetStatusForGroupsRequestBody* Make(FString ContentId, TArray<int64> GroupIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetStatusForGroupsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetStatusForGroupsRequestBody* Serializable, FString& ContentId, TArray<int64>& GroupIds);
};