#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsRequestBody.h"

#include "GetBinaryDownloadUrlsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetBinaryDownloadUrlsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetBinaryDownloadUrlsRequestBody To JSON String")
	static FString GetBinaryDownloadUrlsRequestBodyToJsonString(const UGetBinaryDownloadUrlsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetBinaryDownloadUrlsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ExpirationSeconds, Outer", NativeMakeFunc))
	static UGetBinaryDownloadUrlsRequestBody* Make(TArray<UGetContentRequestBody*> Requests, FOptionalInt64 ExpirationSeconds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetBinaryDownloadUrlsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetBinaryDownloadUrlsRequestBody* Serializable, TArray<UGetContentRequestBody*>& Requests, FOptionalInt64& ExpirationSeconds);
};