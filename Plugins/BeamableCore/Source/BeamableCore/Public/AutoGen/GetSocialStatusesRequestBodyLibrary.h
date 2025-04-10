#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetSocialStatusesRequestBody.h"

#include "GetSocialStatusesRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetSocialStatusesRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="GetSocialStatusesRequestBody To JSON String")
	static FString GetSocialStatusesRequestBodyToJsonString(const UGetSocialStatusesRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make GetSocialStatusesRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSocialStatusesRequestBody* Make(TArray<FString> PlayerIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break GetSocialStatusesRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetSocialStatusesRequestBody* Serializable, TArray<FString>& PlayerIds);
};