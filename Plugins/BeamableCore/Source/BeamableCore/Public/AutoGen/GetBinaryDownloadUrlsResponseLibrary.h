#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsResponse.h"

#include "GetBinaryDownloadUrlsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetBinaryDownloadUrlsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetBinaryDownloadUrlsResponse To JSON String")
	static FString GetBinaryDownloadUrlsResponseToJsonString(const UGetBinaryDownloadUrlsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetBinaryDownloadUrlsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetBinaryDownloadUrlsResponse* Make(TArray<UBinaryContentReference*> Urls, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetBinaryDownloadUrlsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetBinaryDownloadUrlsResponse* Serializable, TArray<UBinaryContentReference*>& Urls);
};