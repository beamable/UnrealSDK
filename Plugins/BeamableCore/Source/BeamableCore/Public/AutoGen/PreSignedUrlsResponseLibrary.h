#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PreSignedUrlsResponse.h"

#include "PreSignedUrlsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPreSignedUrlsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PreSignedUrlsResponse To JSON String")
	static FString PreSignedUrlsResponseToJsonString(const UPreSignedUrlsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PreSignedUrlsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPreSignedUrlsResponse* Make(TArray<UBeamoBasicURLResponse*> Response, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PreSignedUrlsResponse", meta=(NativeBreakFunc))
	static void Break(const UPreSignedUrlsResponse* Serializable, TArray<UBeamoBasicURLResponse*>& Response);
};