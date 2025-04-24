#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetElasticContainerRegistryURI.h"

#include "GetElasticContainerRegistryURILibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetElasticContainerRegistryURILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetElasticContainerRegistryURI To JSON String")
	static FString GetElasticContainerRegistryURIToJsonString(const UGetElasticContainerRegistryURI* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetElasticContainerRegistryURI", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetElasticContainerRegistryURI* Make(FString Uri, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetElasticContainerRegistryURI", meta=(NativeBreakFunc))
	static void Break(const UGetElasticContainerRegistryURI* Serializable, FString& Uri);
};