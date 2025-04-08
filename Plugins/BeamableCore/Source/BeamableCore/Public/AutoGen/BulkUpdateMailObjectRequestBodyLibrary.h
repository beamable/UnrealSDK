#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BulkUpdateMailObjectRequestBody.h"

#include "BulkUpdateMailObjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBulkUpdateMailObjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="BulkUpdateMailObjectRequestBody To JSON String")
	static FString BulkUpdateMailObjectRequestBodyToJsonString(const UBulkUpdateMailObjectRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make BulkUpdateMailObjectRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBulkUpdateMailObjectRequestBody* Make(TArray<UMyMailUpdate*> UpdateMailRequests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break BulkUpdateMailObjectRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBulkUpdateMailObjectRequestBody* Serializable, TArray<UMyMailUpdate*>& UpdateMailRequests);
};