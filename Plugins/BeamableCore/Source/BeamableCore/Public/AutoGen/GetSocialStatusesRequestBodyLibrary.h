#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetSocialStatusesRequestBody.h"

#include "GetSocialStatusesRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetSocialStatusesRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|4 - Json", DisplayName="GetSocialStatusesRequestBody To JSON String")
	static FString GetSocialStatusesRequestBodyToJsonString(const UGetSocialStatusesRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|3 - Backend", DisplayName="Make GetSocialStatusesRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSocialStatusesRequestBody* Make(TArray<FString> PlayerIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|3 - Backend", DisplayName="Break GetSocialStatusesRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetSocialStatusesRequestBody* Serializable, TArray<FString>& PlayerIds);
};