#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetMailDetailsRequestBody.h"

#include "GetMailDetailsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetMailDetailsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="GetMailDetailsRequestBody To JSON String")
	static FString GetMailDetailsRequestBodyToJsonString(const UGetMailDetailsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make GetMailDetailsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetMailDetailsRequestBody* Make(int64 Mid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break GetMailDetailsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetMailDetailsRequestBody* Serializable, int64& Mid);
};