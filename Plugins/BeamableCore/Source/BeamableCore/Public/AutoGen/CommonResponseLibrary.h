#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "CommonResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCommonResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CommonResponse To JSON String")
	static FString CommonResponseToJsonString(const UCommonResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CommonResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCommonResponse* Make(FString Result, TMap<FString, FString> Data, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CommonResponse", meta=(NativeBreakFunc))
	static void Break(const UCommonResponse* Serializable, FString& Result, TMap<FString, FString>& Data);
};