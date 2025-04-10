#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PANamespace.h"

#include "PANamespaceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPANamespaceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="PANamespace To JSON String")
	static FString PANamespaceToJsonString(const UPANamespace* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PANamespace", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPANamespace* Make(FString Namespace, FString Type, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break PANamespace", meta=(NativeBreakFunc))
	static void Break(const UPANamespace* Serializable, FString& Namespace, FString& Type);
};