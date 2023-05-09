#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BulkSendMailRequestBody.h"

#include "BulkSendMailRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBulkSendMailRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - BulkSendMailRequestBody To JSON String")
	static FString BulkSendMailRequestBodyToJsonString(const UBulkSendMailRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make BulkSendMailRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBulkSendMailRequestBody* Make(TArray<USendMailRequestBody*> SendMailRequests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break BulkSendMailRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBulkSendMailRequestBody* Serializable, TArray<USendMailRequestBody*>& SendMailRequests);
};