#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UploadRequests.h"

#include "UploadRequestsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUploadRequestsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UploadRequests To JSON String")
	static FString UploadRequestsToJsonString(const UUploadRequests* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UploadRequests", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static UUploadRequests* Make(TArray<UUploadRequestBody*> Request, FOptionalInt64 PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UploadRequests", meta=(NativeBreakFunc))
	static void Break(const UUploadRequests* Serializable, TArray<UUploadRequestBody*>& Request, FOptionalInt64& PlayerId);
};