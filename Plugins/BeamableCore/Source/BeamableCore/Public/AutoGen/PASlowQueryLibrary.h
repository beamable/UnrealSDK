#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PASlowQuery.h"

#include "PASlowQueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPASlowQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PASlowQuery To JSON String")
	static FString PASlowQueryToJsonString(const UPASlowQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PASlowQuery", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPASlowQuery* Make(FString Line, FString Namespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PASlowQuery", meta=(NativeBreakFunc))
	static void Break(const UPASlowQuery* Serializable, FString& Line, FString& Namespace);
};