#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ArchetypeProxy.h"

#include "ArchetypeProxyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UArchetypeProxyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ArchetypeProxy To JSON String")
	static FString ArchetypeProxyToJsonString(const UArchetypeProxy* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ArchetypeProxy", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UArchetypeProxy* Make(FString Service, FString Namespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ArchetypeProxy", meta=(NativeBreakFunc))
	static void Break(const UArchetypeProxy* Serializable, FString& Service, FString& Namespace);
};