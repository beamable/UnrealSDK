#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PANamespace.h"

#include "PANamespaceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPANamespaceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PANamespace To JSON String")
	static FString PANamespaceToJsonString(const UPANamespace* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PANamespace", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPANamespace* Make(FString Namespace, FString Type, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PANamespace", meta=(NativeBreakFunc))
	static void Break(const UPANamespace* Serializable, FString& Namespace, FString& Type);
};