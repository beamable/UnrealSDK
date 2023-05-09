#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetSocialStatusesRequestBody.h"

#include "GetSocialStatusesRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetSocialStatusesRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetSocialStatusesRequestBody To JSON String")
	static FString GetSocialStatusesRequestBodyToJsonString(const UGetSocialStatusesRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetSocialStatusesRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSocialStatusesRequestBody* Make(TArray<FString> PlayerIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetSocialStatusesRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetSocialStatusesRequestBody* Serializable, TArray<FString>& PlayerIds);
};