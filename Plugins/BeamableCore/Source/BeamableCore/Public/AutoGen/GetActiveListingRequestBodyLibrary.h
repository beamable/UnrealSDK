#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetActiveListingRequestBody.h"

#include "GetActiveListingRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetActiveListingRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetActiveListingRequestBody To JSON String")
	static FString GetActiveListingRequestBodyToJsonString(const UGetActiveListingRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetActiveListingRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Store, Time, Outer", NativeMakeFunc))
	static UGetActiveListingRequestBody* Make(FString Listing, FOptionalString Store, FOptionalString Time, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetActiveListingRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetActiveListingRequestBody* Serializable, FString& Listing, FOptionalString& Store, FOptionalString& Time);
};