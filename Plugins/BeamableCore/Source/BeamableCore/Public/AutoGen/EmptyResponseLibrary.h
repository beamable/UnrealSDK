#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "EmptyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEmptyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EmptyResponse To JSON String")
	static FString EmptyResponseToJsonString(const UEmptyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EmptyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEmptyResponse* Make(FString Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EmptyResponse", meta=(NativeBreakFunc))
	static void Break(const UEmptyResponse* Serializable, FString& Result);
};