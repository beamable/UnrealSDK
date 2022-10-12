
#pragma once

#include "CoreMinimal.h"
#include "GetElasticContainerRegistryURI.h"

#include "GetElasticContainerRegistryURILibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetElasticContainerRegistryURILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetElasticContainerRegistryURI To JSON String")
	static FString GetElasticContainerRegistryURIToJsonString(const UGetElasticContainerRegistryURI* Serializable, const bool Pretty);		
};