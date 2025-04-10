#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PreSignedUrlsResponse.h"

#include "PreSignedUrlsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPreSignedUrlsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="PreSignedUrlsResponse To JSON String")
	static FString PreSignedUrlsResponseToJsonString(const UPreSignedUrlsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PreSignedUrlsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPreSignedUrlsResponse* Make(TArray<UBeamoBasicURLResponse*> Response, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break PreSignedUrlsResponse", meta=(NativeBreakFunc))
	static void Break(const UPreSignedUrlsResponse* Serializable, TArray<UBeamoBasicURLResponse*>& Response);
};