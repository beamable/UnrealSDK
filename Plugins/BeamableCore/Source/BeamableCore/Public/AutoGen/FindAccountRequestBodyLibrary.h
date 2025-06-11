#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FindAccountRequestBody.h"

#include "FindAccountRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFindAccountRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="FindAccountRequestBody To JSON String")
	static FString FindAccountRequestBodyToJsonString(const UFindAccountRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make FindAccountRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFindAccountRequestBody* Make(FString Query, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break FindAccountRequestBody", meta=(NativeBreakFunc))
	static void Break(const UFindAccountRequestBody* Serializable, FString& Query);
};