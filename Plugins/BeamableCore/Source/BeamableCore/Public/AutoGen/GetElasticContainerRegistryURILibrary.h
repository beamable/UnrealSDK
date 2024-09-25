#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/GetElasticContainerRegistryURI.h"

#include "GetElasticContainerRegistryURILibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetElasticContainerRegistryURILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetElasticContainerRegistryURI To JSON String")
	static FString GetElasticContainerRegistryURIToJsonString(const UGetElasticContainerRegistryURI* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetElasticContainerRegistryURI", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetElasticContainerRegistryURI* Make(FString Uri, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetElasticContainerRegistryURI", meta=(NativeBreakFunc))
	static void Break(const UGetElasticContainerRegistryURI* Serializable, FString& Uri);
};