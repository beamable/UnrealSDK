#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveCatalogRequestBody.h"

#include "SaveCatalogRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveCatalogRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="SaveCatalogRequestBody To JSON String")
	static FString SaveCatalogRequestBodyToJsonString(const USaveCatalogRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make SaveCatalogRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveCatalogRequestBody* Make(TArray<UStore*> Stores, TArray<UOfferDefinition*> OfferDefinitions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break SaveCatalogRequestBody", meta=(NativeBreakFunc))
	static void Break(const USaveCatalogRequestBody* Serializable, TArray<UStore*>& Stores, TArray<UOfferDefinition*>& OfferDefinitions);
};