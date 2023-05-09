#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateListingCooldownRequestBody.h"

#include "UpdateListingCooldownRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateListingCooldownRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UpdateListingCooldownRequestBody To JSON String")
	static FString UpdateListingCooldownRequestBodyToJsonString(const UUpdateListingCooldownRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UpdateListingCooldownRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UUpdateListingCooldownRequestBody* Make(FString Symbol, int32 CooldownReduction, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UpdateListingCooldownRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUpdateListingCooldownRequestBody* Serializable, FString& Symbol, int32& CooldownReduction);
};